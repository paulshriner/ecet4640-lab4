/**
 * \addtogroup Process
 * @{
 */

#include "Process.h"
#include "Files.h"
#include "Data.h"
#include "Build.h"
#include "memShare.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

map *student_map;
/// A map of userIDs to integer seconds. These values are subtracted from the current total cumulative time for each user to calculate their cumulative time since the server process started.
map *initial_cumulative_times;

int TerminateExistingServer()
{
    FILE *file = fopen(LOCKFILE, "r");
    if (file == NULL)
    {
        return -1;
    }
    int need_rewrite;
    int pid = 0;
    fscanf(file, "%d %d", &need_rewrite, &pid);
    fclose(file);
    if (pid > 0)
    {
        return kill(pid, SIGTERM);
    }
    return -2;
}

int IndicateRereadNeeded()
{
    FILE *file = fopen(LOCKFILE, "r+");
    if (file == NULL)
    {
        return -1;
    }
    int err = 0;
    err = fseek(file, 0, SEEK_SET);
    if (!err)
    {
        fputc('1', file);
    }
    err = fclose(file);
    return err;
}

int IndicateRereadDone()
{
    FILE *file = fopen(LOCKFILE, "r+");
    if (file == NULL)
    {
        return -1;
    }
    int err = 0;
    err = fseek(file, 0, SEEK_SET);
    if (!err)
    {
        fputc('0', file);
    }
    err = fclose(file);
    return err;
}

short IsRereadNeeded()
{
    FILE *file = fopen(LOCKFILE, "r");
    char firstc = fgetc(file);
    fclose(file);
    return firstc == '1';
}

void SignalHandle(int signo)
{
    printf("Received shutdown signal.\n");
    if (signo == SIGINT || signo == SIGTERM)
    {
        is_stopping = 1;
    }
    // possible feature: add a timeout terminate emergency exit (with graceful shutdown)
    
}

short is_stopping = 0;

// ~~~~~~~~~~~~~~~ CLI Commands ~~~~~~~~~~~~~~~~~~~~~~~~~~

int Initialize()
{
    int err;
    if (!FileExists(STATIC_USER_DATA_FILE))
    {
        printf("%s does not exist. Creating.\n", STATIC_USER_DATA_FILE);
        err = CreateInitialUserDataFile(STATIC_USER_DATA_FILE, Data_IDs, DATA_NUM_RECORDS);
        if (err)
        {
            printf("Problem creating %s!\n", STATIC_USER_DATA_FILE);
        }
    }
    if (!FileExists(STATIC_USER_CUMULATIVE_FILE))
    {
        printf("%s does not exist. Creating.\n", STATIC_USER_CUMULATIVE_FILE);
        err = CreateInitialCumulativeFile(STATIC_USER_CUMULATIVE_FILE);
        if (err)
        {
            printf("Problem creating %s!\n", STATIC_USER_CUMULATIVE_FILE);
        }
    }
    PopulateStudents(Data_IDs, Data_Names, DATA_NUM_RECORDS);
    student_map = NewMap(50);
    BuildStudentMap(student_map, students, DATA_NUM_RECORDS);
    err = FillStudentMapFromFile(student_map, STATIC_USER_DATA_FILE, Data_IDs, DATA_NUM_RECORDS);
    if (err)
    {
        printf("Problem filling student map from %s!\n", STATIC_USER_DATA_FILE);
    }
    printf("Student data retrieved from file.\n");

    initial_cumulative_times = NewMap(50);
    err = ReadInitialCumulative(initial_cumulative_times, STATIC_USER_CUMULATIVE_FILE);
    if (err)
    {
        printf("Failed to read %s. Cumulative times may be wrong!", STATIC_USER_CUMULATIVE_FILE);
    }

    dirty = 0;

    int shmid = CreateSharedMemory();
    if (shmid == -1)
    {
        DestroySharedMemory();
        shmid = CreateSharedMemory();
    }
    printf("Shared memory allocated.\n");
    return shmid;
}

void Process(int shm_id)
{
    if (IsRereadNeeded())
    {
        printf("\nReread indicated - rechecking user data file.");
        FillStudentMapFromFile(student_map, STATIC_USER_DATA_FILE, Data_IDs, DATA_NUM_RECORDS);
        IndicateRereadDone();
    }
    SetAllStudentsInactive(students, DATA_NUM_RECORDS);
    int err = PipeAcpToStudentMap(student_map);
    if (err)
    {
        printf("Error piping ac -p command! \n");
    }
    else
    {
        CalculateCumulative(students, DATA_NUM_RECORDS, initial_cumulative_times);
    }
    err = PipeWhoToStudentMap(student_map);
    if (err)
    {
        perror("Error updating from who!");
    }
    if (dirty)
    {
        err = WriteStudentArrayToFile(students, DATA_NUM_RECORDS, STATIC_USER_DATA_FILE);
        if (err)
        {
            printf("\nError updating %s!", STATIC_USER_DATA_FILE);
        }
        else
        {
            dirty = 0;
        }
    }
    void *ptr = GetMemoryPointer(shm_id);
    if (ptr == (void *)-1)
    {
        perror("Error attaching to shared memory");
    }
    else
    {
        WriteStudentsToMemory(ptr, students, DATA_NUM_RECORDS);
        ReleaseMemoryPointer(ptr);
    }
}

void HelpCommand()
{
    printf("\nUsage: server [OPTION]\n\n");
    printf("Options: \n");
    printf("\thelp\t\t\tShows the possible program commands\n");
    printf("\treset\t\t\tRegenerates the user data file\n");
    printf("\tstop\t\t\tStops an existing server process if it is running\n");
    printf("\trun\t\t\tCreates a new server with output to the shell if a server isn't already running.\n");
    printf("\theadless\t\tCreates a new headless server if a server isn't already running.\n\n");
}

void RunCommand()
{
    printf("\nRunning server.\n");
    if (DoesLockfileExist())
    {
        printf("\nServer is already running. Run 'server stop' to shut it down first.\n");
        return;
    }
    int err = CreateLockfile();
    if (err)
    {
        printf("\nFailed to create lockfile! Exiting.\n");
        return;
    }
    int shm_id = Initialize();
    signal(SIGTERM, SignalHandle);
    signal(SIGINT, SignalHandle);
    printf("Server started.\n");
    fflush(stdout);
    while (!is_stopping)
    {
        Process(shm_id);
        sleep(1);
    }
    printf("Server shutting down.\n");
    err = DeleteLockfile();
    if (err)
    {
        printf("Failed to delete lockfile!\n");
    }
    err = DestroySharedMemory();
    if (err)
    {
        printf("Failed to destroy shared memory!\n");
    }
    printf("Server terminated.\n");
}

void StopCommand()
{
    printf("\nStopping server...\n");
    int err = TerminateExistingServer();
    if (err != 0)
    {
        if (err == -1)
        {
            printf("Server isn't running.\n");
        }
        else if (err == -2)
        {
            printf("Lockfile did not contain a valid process id!\n");
        }
        else
        {
            printf("Sending terminate signal failed!\n");
        }
    }
    else
    {
        printf("Server terminated.\n");
    }
}

void ResetCommand()
{
    int err;

    if (FileExists(STATIC_USER_DATA_FILE))
    {
        printf("User data file exists. Deleting...\n");
        remove(STATIC_USER_DATA_FILE);
    }

    printf("Creating new data file.\n");
    err = CreateInitialUserDataFile(STATIC_USER_DATA_FILE, Data_IDs, DATA_NUM_RECORDS);
    if (err)
    {
        printf("Problem creating %s!\n", STATIC_USER_DATA_FILE);
    }
    else
    {
        printf("%s created.\n", STATIC_USER_DATA_FILE);
    }

    printf("Creating new cumulative file.\n");
    err = CreateInitialCumulativeFile(STATIC_USER_CUMULATIVE_FILE);
    if (err)
    {
        printf("Problem creating %s!\n", STATIC_USER_CUMULATIVE_FILE);
    }
    else
    {
        printf("%s created.\n", STATIC_USER_CUMULATIVE_FILE);
    }

    if (DoesLockfileExist())
    {
        printf("Indicated re-read to running server process.\n");
        IndicateRereadNeeded();
    }
}

void RunHeadless(char *processName)
{
    if (DoesLockfileExist())
    {
        printf("Server process already running.\n");
        return;
    }
    char commandFront[] = " nohup ";
    char commandEnd[] = " run & exit";
    size_t comm_length = strlen(commandFront) + strlen(commandEnd) + strlen(processName) + 1;
    char *commandFull = malloc(comm_length * sizeof(char));
    memset(commandFull, 0, comm_length * sizeof(char));
    strcpy(commandFull, commandFront);
    strcat(commandFull, processName);
    strcat(commandFull, commandEnd);

    printf("Executing: %s\n", commandFull);
    popen(commandFull, "we");
    printf("Server running headlessly.\n");
}
/**
 * @}
*/
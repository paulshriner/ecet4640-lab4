#include "Process.h"

#include "Files.h"
#include "Data.h"
#include "Build.h"
#include "memShare.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

map *student_map;

// ~~~~~~~~~~~~~~~ Lockfile Commands ~~~~~~~~~~~~~~~~~~~~~

short DoesLockfileExist()
{
    return FileExists(LOCKFILE);
}

int CreateLockfile()
{
    FILE * file = fopen(LOCKFILE, "w");
    if(file == NULL) {
        return -1;
    }
    fprintf(file, "0 %d", getpid());
    fclose(file);
    return 0;
}

int DeleteLockfile() {
    return remove(LOCKFILE);
}

int TerminateExistingServer() {
    FILE * file = fopen(LOCKFILE, "r");
    if(file == NULL) {
        return -1;
    }
    int need_rewrite;
    int pid = 0;
    fscanf(file, "%d %d", &need_rewrite, &pid);
    fclose(file);
    if(pid > 0) {
        return kill(pid, SIGTERM);
    }
    return -2;
}

int IndicateRereadNeeded() {
    FILE * file = fopen(LOCKFILE, "r+");
    if (file == NULL) {
        return -1;
    }
    int err = 0;
    err = fseek(file, 0, SEEK_SET);
    if(!err) {
        fputc('1', file);
    }
    err = fclose(file);
    return err;
}

int IndicateRereadDone() {
    FILE * file = fopen(LOCKFILE, "r+");
    if (file == NULL) {
        return -1;
    }
    int err = 0;
    err = fseek(file, 0, SEEK_SET);
    if(!err) {
        fputc('0', file);
    }
    err = fclose(file);
    return err;
}

short IsRereadNeeded() {
    FILE * file = fopen(LOCKFILE, "r");
    char firstc = fgetc(file);
    fclose(file);
    return firstc == '1';
}

void SignalHandle(int signo) {
    printf("\nReceived shutdown signal.");
    if(signo == SIGINT || signo == SIGTERM) {
        is_stopping = 1;
    }
}

short is_stopping = 0;

// ~~~~~~~~~~~~~~~ CLI Commands ~~~~~~~~~~~~~~~~~~~~~~~~~~

int Initialize()
{
    int err;
    if (!FileExists(STATIC_USER_DATA_FILE))
    {
        printf("\n%s does not exist. Creating.", STATIC_USER_DATA_FILE);
        err = CreateInitialUserDataFile(STATIC_USER_DATA_FILE, Data_IDs, DATA_NUM_RECORDS);
        if (err)
        {
            printf("\nProblem creating %s!", STATIC_USER_DATA_FILE);
        }
    }
    PopulateStudents(Data_IDs, Data_Names, DATA_NUM_RECORDS);
    student_map = NewMap(50);
    BuildStudentMap(student_map, students, DATA_NUM_RECORDS);
    err = FillStudentMapFromFile(student_map, STATIC_USER_DATA_FILE, Data_IDs, DATA_NUM_RECORDS);
    if (err)
    {
        printf("\nProblem filling student map from %s!", STATIC_USER_DATA_FILE);
    }
    printf("\nStudent data retrieved from file.");

    dirty = 0;

    int shmid = CreateSharedMemory();
    if (shmid == -1)
    {
        DestroySharedMemory();
        shmid = CreateSharedMemory();
    }
    printf("\nShared memory allocated.");
    return shmid;
}

void Process(int shm_id)
{
    if(IsRereadNeeded()) {
        printf("\nReread indicated - rechecking user data file.");
        FillStudentMapFromFile(student_map, STATIC_USER_DATA_FILE, Data_IDs, DATA_NUM_RECORDS);
        IndicateRereadDone();
    }
    SetAllStudentsInactive(students, DATA_NUM_RECORDS);
    int err = UpdateFromWho(student_map);
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
    printf("\tclear\t\t\tClears the shared virtual memory segment\n");
    printf("\treset\t\t\tRegenerates the user data file\n");
    printf("\tstop\t\t\tStops an existing server process if it is running\n");
    printf("\trun\t\t\tStops any existing server, then creates a new one\n\n");
}

void RunCommand()
{
    if(DoesLockfileExist()) {
        printf("\nServer is already running. Run 'server stop' to shut it down first.\n");
        return;
    }
    int err = CreateLockfile();
    if(err) {
        printf("\nFailed to create lockfile! Exiting.\n");
        return;
    }
    int shm_id = Initialize();
    signal(SIGTERM, SignalHandle);
    signal(SIGINT, SignalHandle);
    printf("\nServer started.\n");
    fflush(stdout);
    while (!is_stopping)
    {
        Process(shm_id);
        sleep(1);
    }
    printf("Server shutting down.\n");
    err = DeleteLockfile();
    if(err) {
        printf("Failed to delete lockfile!\n");
    }
    err = DestroySharedMemory();
    if(err) {
        printf("Failed to destroy shared memory!\n");
    }
    printf("Server terminated.\n");
}

void StopCommand()
{
    printf("\nStopping server.\n");
    int err = TerminateExistingServer();
    if(err) {
        if(err == -1) {
            printf("Failed to find lockfile!\n");
        } else if(err == -2) {
            printf("Lockfile did not contain a valid process id!\n");
        } else {
            printf("Sending terminate signal failed!\n");
        }
        printf("Server stop may have failed. \n");
    }
    printf("Server terminated.\n");
}

void ClearCommand()
{
    DestroySharedMemory();
    printf("\nVirtual memory segment is now deallocated\n\n");
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
        printf("\nProblem creating %s!", STATIC_USER_DATA_FILE);
    } else {
        printf("Data file created.\n");
        if(DoesLockfileExist()) {
            printf("Indicated re-read to running server process.\n");
            IndicateRereadNeeded();
        }
    }
}

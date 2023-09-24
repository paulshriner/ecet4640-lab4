#include "Process.h"

#include "Files.h"
#include "Data.h"
#include "Build.h"
#include "memShare.h"
#include <errno.h>
#include <stdio.h>

map *student_map;

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
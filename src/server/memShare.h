#ifndef MEM_SHARE_H
#define MEM_SHARE_H

#include <sys/shm.h>
#include <sys/ipc.h>
#include "Data.h"
#include "Student.h"

/*
    The shared memory key that clients and servers will use to identify the segment.
*/
#define MEM_KEY 0x727

/*
    Memory permissions are:
        Self:   RW    110 = 6
        Group:  R     100 = 4
        Others: R     100 = 4
        - All groups can read.
        - Self can write.
        - None can execute.
*/
#define MEM_PERMISSIONS 644

/*
    The memory allocation must as large as the data size times the number of records.
*/
#define MEM_SIZE DATA_SIZE *DATA_NUM_RECORDS

/**
    CreateSharedMemory retrieves a shared memory ID that can be used to access or delete shared memory.

    @returns A shared memory ID that can be used with other 'shm' commands to access shared memory.
*/
int CreateSharedMemory();

/**
    Flags the shared memory segment for deallocation. Returns the result of that operation.

    @returns -1 if destroy flag failed.
*/
int DestroySharedMemory();

// Find out what to return for attatching structuring to memory

// find out what info is needed for detatching from memory

#endif
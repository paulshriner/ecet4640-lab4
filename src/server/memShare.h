#ifndef MEM_SHARE_H
#define MEM_SHARE_H

#include <sys/shm.h>
#include <sys/ipc.h>
#include "Data.h"

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
#define MEM_PERMISSIONS 0664

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

    @returns 0 if succesful. 1 if not succesful. Errno will be set.
*/
int DestroySharedMemory();

/** 
    "Attaches" to the shared memory, returning a memory pointer to the shared memory.

    Calls 'shmat(shared_mem_id, NULL, 0)`;

    void * will be equal to -1 if it fails. 
 
*/
void * GetMemoryPointer(int shared_mem_id);

/*
    Release a shm memory pointer.
*/
int ReleaseMemoryPointer(void *shmaddr);


void FillSharedMemory(void * shared_memory, Student* students_arr, int arr_length);

/**
    Fills the shared memory with the student's array.
*/
// int FillSharedMemory(int shared_memory_id, Student* students_arr, int arr_size);

// Find out what to return for attatching structuring to memory

// find out what info is needed for detatching from memory

#endif
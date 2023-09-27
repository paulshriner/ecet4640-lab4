#ifndef MEM_SHARE_H
#define MEM_SHARE_H
/**
 * \file memShare.h
 * @brief Declarations for functions that operate on a shared memory segment.
   @details To share data to clients program uses shared memory

   - MEM_KEY is the key to access the shared memory and clients must have this info
   - MEM_PERMISSIONS who has read, write permissions of the shared memory segment
   - MEM_SIZE the total size of the shared memory allocation
 */

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

    @returns A shared memory ID that can be used with other 'shm' commands to access shared memory, -1 if an error has occured
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

    @param shared_mem_id The id of the shared memory
    @returns A pointer to the shared memory, or -1 if it fails.

*/
void *GetMemoryPointer(int shared_mem_id);

/**
    Release a shm memory pointer.
    @param shmaddr The memory pointer to release.
    @returns Whether the operation was succesful.
*/
int ReleaseMemoryPointer(void *shmaddr);

#endif
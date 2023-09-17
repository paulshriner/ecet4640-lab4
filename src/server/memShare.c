#include "memShare.h"

/*
    Todo: Error handling and printing
*/

int CreateSharedMemory()
{
    return shmget(MEM_KEY, MEM_SIZE, IPC_CREAT | MEM_PERMISSIONS);
}

int DestroySharedMemory()
{
    int shm_id = shmget(MEM_KEY, MEM_SIZE, 0);
    return shmctl(shm_id, IPC_RMID, 0);
}
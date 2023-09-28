/**
 * \addtogroup memShare
 * @{ 
 */
#include "memShare.h"
#include <string.h>
#include <stdio.h>

int CreateSharedMemory()
{
    return shmget(MEM_KEY, MEM_SIZE, IPC_CREAT | MEM_PERMISSIONS);
}

int DestroySharedMemory()
{
    int shm_id = shmget(MEM_KEY, MEM_SIZE, 0);
    int control_result = shmctl(shm_id, IPC_RMID, 0);
    if (control_result != -1)
        return 0;
    return control_result;
}

void *GetMemoryPointer(int shared_mem_id)
{
    return shmat(shared_mem_id, NULL, 0);
}

int ReleaseMemoryPointer(void *shmaddr)
{
    return shmdt(shmaddr);
}
/**
 * @}
*/
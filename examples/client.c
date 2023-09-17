/*
 *  shm2.c - demo program to show use of Unix shared memory facility
 *	   - DATA "CONSUMER" AGENT
 *  10-Oct-94 :jss
 */

#include <stdio.h>     // for standard system I/O stuff
#include <errno.h>     // for error handling on system calls
#include <sys/types.h> // for system defined types
#include <sys/ipc.h>   // for IPC permission structure
#include <sys/shm.h>   // for shared memory facility defines

#define SHMKEY 0x77000 + 01

main()
{
    int shm_id, i, *z; // z will point to shared memory array

    //  --------------------------------------------------------------------
    //  call system library function to get pre-existing shared memory
    //  --------------------------------------------------------------------
    shm_id = shmget(SHMKEY, 0, 0);

    if (shm_id == -1) // check shmget() return value
    {
        printf("\nError: shmget() failed, errno = %i\n", errno);
        perror("shmget()");
        exit(-1);
    }
    else
        printf("\nshmget() successful, shm_id = %i\n", shm_id);

    //  --------------------------------------------------------------------
    //  attach variable z to shared memory segment
    //  --------------------------------------------------------------------
    z = (int *)shmat(shm_id, 0, SHM_RDONLY);
    if ((int)z == -1)
    {
        printf("Error: shmat() failed, errno = %i\n", errno);
        perror("shmat()");
        exit(-1);
    }

    //  access data from shared memory region
    printf("array z begins at 0x%08x\nContents of array z:\n", z);
    for (i = 0; i < 10; i++)
        printf("\tz[%i] = %i\n", i, z[i]);
    putchar('\n');

    //  --------------------------------------------------------------------
    //  done with shared memory, detach from it
    //  --------------------------------------------------------------------
    shmdt((void *)z);

    return (0);
}

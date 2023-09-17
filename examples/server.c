/*
 *  shm1.c - demo program to show use of Unix shared memory facility
 *	   - DATA "SUPPLIER" AGENT
 *  10-Oct-94 :jss - original writing
 *   5-Mar-99 :jss - updated for Solaris
 *
 *  important things to look at for this program:
 *	include files: <sys/ipc.h>, <sys/shm.h>
 *	man pages: intro(2), shmget(2), shmop(2), shmctl(2)
 *	man pages: ipcs(1), ipcrm(1)
 */

#include <stdio.h>     // for standard system I/O stuff
#include <errno.h>     // for error handling on system cal
#include <sys/types.h> // for system defined types
#include <sys/ipc.h>   // for IPC permission structure
#include <sys/shm.h>   // for shared memory facility defines

#define SHMKEY 0x77000 + 01 // shared memory "key"
#define NSECS 30            // number of seconds to live

// define array of integers to be available via "shared memory"
int x[] = {-1, 0, 1, 2, 3, 5, 8, 13, 21, 34};

main()
{
    int shm_id, shm_addr;
    int n, i, *y;

    //  display some interesting stuff
    n = sizeof(x) / sizeof(int); // calculates # elements in x[]
    printf("\narray x begins at 0x%08x, sizeof(x)=%i bytes (%i elements)\n\n",
           x, sizeof(x), n);

    //  --------------------------------------------------------------------
    //  call system library function to create new shared memory region
    //    from ipc.h:
    //      IPC_CREAT = create memory region if key doesn't exist
    //      IPC_EXCL  = fail if key already exists
    //  --------------------------------------------------------------------
    shm_id = shmget(SHMKEY, sizeof(x), IPC_CREAT | 0666);

    if (shm_id == -1) // check shmget() return value
    {
        printf("Error: shmget() failed, errno = %i\n", errno);
        perror("shmget()");
        exit(-1);
    }
    else
        printf("shmget() successful, shm_id = %i\n", shm_id);

    //  --------------------------------------------------------------------
    //  attach variable y to shared memory segment
    //  --------------------------------------------------------------------
    //    shm_addr = (int) shmat( shm_id, 0, 0 );
    //    y = (int *) shm_addr;
    y = (int *)shmat(shm_id, 0, 0);

    printf("shm_addr = 0x%08x, y = 0x%08x\n", shm_addr, y);
    if ((int)y == -1) // check shmat() return value
    {
        printf("Error: shmat() failed, errno = %i\n", errno);
        perror("shmat()");
        exit(-1);
    }
    //  copy data to shared memory region
    printf("ready to copy\n");
    for (i = 0; i < n; i++)
        y[i] = x[i];

    //  twiddle thumbs for awhile
    printf("\nSleeping for %i seconds...\n\n", NSECS);
    sleep(NSECS);
    printf("\nYawn, that was a nice nap...\n\n");

    //  --------------------------------------------------------------------
    //  done with shared memory, detach and release it with error checking
    //  --------------------------------------------------------------------
    shmdt((void *)shm_addr);
    if (shmctl(shm_id, IPC_RMID, NULL) == -1)
    {
        printf("Error: shmctl(IPC_RMID) failed, errno = %i\n", errno);
        perror("shmctl(IPC_RMID)");
        exit(-1);
    }

    return (0);
}

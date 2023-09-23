#include "Process.h"
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    srand(time(NULL)); // seed the randomizer
    int shm_id = Initialize();
    printf("\nStarting 'server'.\n");
    fflush(stdout);
    while (1)
    {
        Process(shm_id);
        sleep(1);
    }
    return 0;
}

//     Called when the 'create' argument is passed.

//     Creates and fills the shared memory segment.
// */
// void CreateCommand()
// {
//     printf("\nCreating shared memory.");
//     int has_error = CreateAndPopulate();
//     if (has_error)
//     {
//         printf("\nProblem creating shared memory. Code returned: %d", has_error);
//         perror("\nLast Error: ");
//     }
//     else
//     {
//         printf("\nSegment created and filled.\n");
//     }
// }

// /*
//     Called when the 'destroy' argument is passed.

//     Removes the shared memory segment.
// */
// void DestroyCommand()
// {
//     printf("\nDestroying shared memory.");
//     int has_error = DestroySharedMemory();
//     if (has_error)
//     {
//         printf("\nProblem destroying shared memory. Code returned: %d", has_error);
//         perror("\nLast Error: ");
//     }
//     else
//     {
//         printf("\nSegment destroyed.\n");
//     }
// }

// /*
//     Called when no arguments are passed. Attempts to create and fill the shared memory segment. If that fails, it attempts to remove that segment.
// */
// void CreateOrDestroy()
// {
//     int has_error = CreateAndPopulate();
//     if (has_error)
//     {
//         DestroyCommand();
//     }
//     else
//     {
//         printf("\nCreated shared memory segment.\n");
//     }
// }
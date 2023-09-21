#include "stdio.h"
#include "memShare.h"
#include "string.h"
#include "Build.h"
#include "error.h"
#include "Files.h"


/*
    Called when the 'create' argument is passed.

    Creates and fills the shared memory segment.
*/
void CreateCommand() {
    printf("\nCreating shared memory.");
    int has_error = CreateAndPopulate();
    if(has_error) {
        printf("\nProblem creating shared memory. Code returned: %d", has_error);
        perror("\nLast Error: ");
    } else {
        printf("\nSegment created and filled.\n");
    }
}

/*
    Called when the 'destroy' argument is passed.

    Removes the shared memory segment.
*/
void DestroyCommand() {
    printf("\nDestroying shared memory.");
    int has_error = DestroySharedMemory();
    if(has_error) {
        printf("\nProblem destroying shared memory. Code returned: %d", has_error);
        perror("\nLast Error: ");
    } else {
        printf("\nSegment destroyed.\n");
    }
}

/*
    Called when no arguments are passed. Attempts to create and fill the shared memory segment. If that fails, it attempts to remove that segment. 
*/
void CreateOrDestroy() {
    int has_error = CreateAndPopulate();
    if(has_error) {
        DestroyCommand();
    } else {
        printf("\nCreated shared memory segment.\n");
    }

}

int main(int argc, char **argv)
{
    CreateInitialLoginTxt();
    
    // if(argc > 1) {
    //     if(strcmp(argv[1], "create") == 0) {
    //         CreateCommand();
    //     } else if(strcmp(argv[1], "destroy") == 0) {
    //         DestroyCommand();
    //     } else {
    //         printf("\nYour argument was not understood. Try 'create' or 'destroy'. \n");
    //     }
    // } else {
    //     printf("\nToggling memory.");
    //     CreateOrDestroy();
    // }
    // return 0;
}
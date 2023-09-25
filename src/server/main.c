#include "Process.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    srand(time(NULL)); // seed the randomizer

    if (argc <= 1 || argc >= 3) 
    {
        printf("You entered too few or many options!\n");
        HelpCommand();
    } 
    else if (strcmp(argv[1], "help") == 0)
    {
        HelpCommand();
    }
    else if (strcmp(argv[1], "reset") == 0) 
    {
        ResetCommand();
    }
    else if (strcmp(argv[1], "stop") == 0 || strcmp(argv[1], "end") == 0 || strcmp(argv[1], "close") == 0) 
    {
        StopCommand();
    }
    else if(strcmp(argv[1], "headless") == 0 )
    {
        RunHeadless(argv[0]);
    }
    else if (strcmp(argv[1], "run") == 0 || strcmp(argv[1], "start") == 0) 
    {
        RunCommand();
    }
    else if (strcmp(argv[1], "delete-lockfile") == 0) 
    {   // an admin debug command; not meant to be called
        printf("Deleting lockfile.\n");
        DeleteLockfile();
    } 
    else {
        printf("Unknown option!\n");
        HelpCommand();
    }
    return 0;
}

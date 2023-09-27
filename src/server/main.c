#include "Process.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/**
 \mainpage

  This program reads user information using the `who` command and publishes that information to shared virtual memory for client processes to read. It updates every second.

  The main.c page is a good starting point for following the call graph.

  Here is a general call graph at a glance:

  ![Program Call graph](full-no-library.png){width=100%}

  ## About
  Created for Computer Networking, September 2023, by [Karl Miller](https://quaffingcode.com), Paul Shriner, and Christian Messmer.

*/

/**
 * @brief Program entry.
 *
 * Parses arguments and calls the appropriate Process.h function.
 *
 * @param argc The argument count.
 * @param argv The argument values.
 */
int main(int argc, char **argv)
{
    srand(time(NULL)); // seed the randomizer

    if (argc <= 1 || argc >= 3)
    {
        printf("Too few or many options!\n");
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
    else if (strcmp(argv[1], "headless") == 0)
    {
        RunHeadless(argv[0]);
    }
    else if (strcmp(argv[1], "run") == 0 || strcmp(argv[1], "start") == 0)
    {
        RunCommand();
    }
    else if (strcmp(argv[1], "delete-lockfile") == 0)
    { // an admin debug command; not meant to be called
        printf("Deleting lockfile.\n\n");
        DeleteLockfile();
    }
    else
    {
        printf("Unknown option!\n");
        HelpCommand();
    }
    return 0;
}

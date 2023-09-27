/**
    \file main.c
    \brief Program entry point.
*/
#include "Process.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/**
 \mainpage

 # Intro

  This program reads user information using the `who` command and publishes that information to shared virtual memory for client processes to read. It updates every second.

  The main.c page is a good starting point for following the program control flow.
  
 # Overview

    The first time the program runs, it generates files containing static user data and the cumulative login times for each user. As the server runs, it will recheck the result of 'who' and 'ac -p' to update the student's cumulative login times, determine which students are actively logged in, and what time they last logged in. This information is stored in a read-shared memory segment so clients can access it using the shared memory key. If necessary, it also updates student information in the file. 

    Only one server process should be running at a given time. To that end, a running server creates a lockfile in the /tmp folder and deletes the lockfile when it is done. New servers will not be started if a lockfile exists, but the running server can be stopped by passing the command line argument 'stop' to the binary. There are other command line arguments available, as detailed below.

    # Arguments for program
    | Argument | Description | Calls |
    |----------|--------|-------|
    | help     | Prints usage of program. | HelpCommand() |
    | reset    | Resets and re-randomizes the static user data and restarts the cumulative time tracking. | ResetCommand() |
    | stop     | Stops an existing server process if it is running. | StopCommand() |
    | headless | Runs the program headlessly in the background if it is not already running. | RunHeadless() |
    | run      | Runs the server in the current program if it is not already running. | RunCommand() |

    

  \author [Karl Miller](https://quaffingcode.com)
  \author Paul Shriner
  \author Christian Messmer
*/

/**
 \page Compilation

 # Compilation Pipelines

 There are several compilation pipelines, which are described in more detail in the Makefile comments. 

 The first is for making and running the regular server process. Calling `make` executes this. It uses the files in `src/server` to generate the binary and runs it. This will output the help for the server command. Executing `make server` will make the server binary without running it.  

 Second is for making the test client process with `make client`. This uses the files from `src/client`. The client process is not documented as it was not part of the program objective, and to avoid further documentation inflation.

 Third is for making the test binary. This compiles the files in `tests` and the files in `src/server`, but excludes `src/main.c` so that `tests/main_test.c` will be the program entry point instead. The tests use [CuTest](https://cutest.sourceforge.net/). The tests are not documented here in order to not inflate the documentation size any further.

 # Compiling and Running

 1. Copy the .zip file to the server
 2. Extract the zip file.
 3. Enter the unzipped folder.
 4. Run `make server`
 5. Run `./server run` to run the server in the shell.
 6. Press ctrl-c to stop the server.
 7. Run `./server headless` to run the server headlessly using nohup.
 8. Run `./server reset` to re-randomize the user data and reset the login times.
 9. Run `./server stop` to shut down the server. (You may want to leave it running so clients can connect to it)

 # Screenshot of Compilation

 ![Compiling on draco1](compilation.png)

 # Cleaning

 There are two clean commands.
 
 `make clean` will clean all .o files and binaries. 
 
 `make cleanf` will also remove the files generated on server initialization, such as the cumulative login file and user data file. 
 
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
    else if (strcmp(argv[1], "stop") == 0 || strcmp(argv[1], "end") == 0 || strcmp(argv[1], "close") == 0 || strcmp(argv[1], "exit") == 0)
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
    else
    {
        printf("Unknown option!\n");
        HelpCommand();
    }
    return 0;
}

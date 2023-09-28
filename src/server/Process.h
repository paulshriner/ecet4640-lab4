#ifndef Process_h
#define Process_h
/**
 * \defgroup Process
    @brief Functions that manage control flow.
    @details This module handles the processes that this server might execute. It calls functions from the other modules to realize program changes.

    It contains the main update loop for a running server, Process(), as well as functions for implementing the different command line argument driven procedures.
*/
#include "map.h"

/**
    Reads the lockfile to get the ID of the process that created it.

    Sends a SIGTERM signal to that process.

    @warning lockfile should be confirmed to exist
    @returns -1 if file doesn't exist, -2 if no valid process ID existed in the file, 1 if sending the kill signal failed.
*/
int TerminateExistingServer();

/**
    If we reset the user data, we need to indicate to the running process that a re-read is needed. This changes the flag in the lockfile to 1, but keeps the same process ID as before there.

    @warning should only be called by non main processes

    @returns -1 if lockfile not found, 0 if success, or an error number if some other error
*/
int IndicateRereadNeeded();

/**
    If we re-read the users file, we can indicate that we have done so by setting the re-read flag back to 0.

    @warning should only be called by main process.
    @returns 0 on success, -1 if the file was not found, otherwise an error number produced by fclose.
*/
int IndicateRereadDone();

/**
    Reads the lockfile for the re-read flag.

    @warning Lockfile should exist - should be called by the server in the main process loop
    @returns 0 if the Lockfile starts with '0', 1 if the Lockfile starts with '1'.
*/
short IsRereadNeeded();

/**
    Called by a new server process, telling this server process to shut down. This sets 'is_stopping' to true, which shuts down the server gracefully, writing any necessary data to the user data file, then deleting the lockfile.

    @param signo The signal number will be SIGTERM from the other server process or SIGINT if interrupted from the console.
*/
void SignalHandle(int signo);

/**
    If 0, the server is running and looping, re-reading and writing every second. If 1, it is stopping and shutting down.
*/
extern short is_stopping;

// ~~~~~~~~~~~~~~~ CLI Commands ~~~~~~~~~~~~~~~~~~~~~~~~~~

extern map *student_map;

/**
    Run once at program start. Calls functions from other modules to do the following:

    @note (1) - Create an initial user data file if it doesn't exist.
    @note (2) - Initialize the students array.
    @note (3) - Initialize the students map.
    @note (4) - Read the data from the user data file into the map/array.
    @note (5) - Initializes the shared memory segment.
    @return The ID of the shared memory segment or -1 if an error has occured.
*/
int Initialize();

/**
    Called repeatedly with a delay.

    @note (1) - Sets all users to inactive.
    @note (2) - Reads the result of the `who` command, setting some users to active, and possibly changing 'dirty' and last login times.
    @note (3) - Overwrites the user data file if we are dirty.
    @note (4) - Sets dirty to false.
    @note (5) - Rewrites the shared memory.

    @param shm_id The ID of the shared memory segment.

*/
void Process(int shm_id);

/**
    Deletes and recreates the static-user-data file and cumulative login file.

    @note To execute the command, pass "reset" as an argument to the program.
    @warning This will clear login times.
*/
void ResetCommand();

/**
    Stops an existing server process if it is running by calling `kill` on the pid stored in the Lockfile.

    @note To execute the command, pass "stop" as an argument to the program.
*/
void StopCommand();

/**
 * @brief Runs the server if it doesn't already exist.
 * @details This function begins the Process() loop. It is ultimately called via two cli arguments; "run" and "headless".
*/
void RunCommand();

/**
    Displays the commands available to the user.

    @note To execute the command, pass "help" as an argument to the program.
    @note This command will also run if arg num is incorrect or if invalid option is entered.
*/
void HelpCommand();

/**
    Uses nohup `./{processName} run` to run the process headlessly.
    @param processName The name of the currently running process, by default, 'server'.
*/
void RunHeadless(char *processName);
/**
 * @}
*/

#endif

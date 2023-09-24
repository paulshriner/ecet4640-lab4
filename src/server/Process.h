#ifndef Process_h
#define Process_h
/*
    This module handles the processes that this server might execute. It calls functions from the other modules to realize program changes.
*/
#include "map.h"


/**
    The lockfile serves as a signal to subsequent processes as to whether or not server is already running.

    It carries two pieces of data. The first is a 0 or 1, telling the server whether user data has been reset and needs to be re-read.

    The second is an int corresponding to the process ID, so a close signal can be sent to the running process when a user enters `server close`.

*/
#define LOCKFILE "/tmp/ecet-server.lock"

// ~~~~~~~~~~~~~~~ Lockfile Commands ~~~~~~~~~~~~~~~~~~~~~

/**
    Determines if lockfile exists, which indicates that a server process is already running.

    @returns 0 if lockfile does not exist, 1 if it does.
*/
short DoesLockfileExist();

/**
    Creates a lockfile. 
    
    @warning This should only be called by a running server process when a lockfile does not already exist.

    The lockfile will carry a 'data reset' signal and a process ID. CreateLockfile will write the current processes PID.
    @returns -1 if fopen failed, otherwise 0.
*/
int CreateLockfile();

/**
    Deletes the lockfile.
    @returns 0 on success, -1 on failure.
*/
int DeleteLockfile();

/**
    Reads the lockfile to get the ID of the process that created it.

    Sends a SIGTERM signal to that process. 

    @warning lockfile should be confirmed to exist
    @returns -1 if file doesn't exist, -2, if no valid process ID existed in the file, 1 if sending the kill signal failed.
*/
int TerminateExistingServer();

/**
    If we reset the user data, we need to indicate to the running process that a re-read is needed. This changes the flag in the lockfile to 1, but keeps the same process ID as before there. 

    @warning should only be called by non main processes

    @returns -1 if lockfile not found., 0 if success, or an error number if some other error
*/
int IndicateRereadNeeded();

/**
    If we re-read the users file, we can indicate that we have done so by setting the re-read flag back to 0. 

    @warning should only be called by main process.
*/
int IndicateRereadDone();

/**
    Reads the lockfile for the reread flag.

    @warning Lockfile should exist - should be called by the server in the main process loop
*/
short IsRereadNeeded();

/**
    Called by a new server process, telling this server process to shut down. This sets 'is_stopping' to true, which shuts down the server gracefully, writing any necessary data to the user data file, then deleting the lockfile. 

    @param signo The signal number. Will be SIGTERM from the other server process or SIGINT if interrupted from the console.

    @returns 0 on success, -1 on error
*/
void SignalHandle(int signo);

/**
    If 0, the server is running and looping, rereading and writing every second. If 1, it is stopping and shutting down. 
*/
extern short is_stopping;


// ~~~~~~~~~~~~~~~ CLI Commands ~~~~~~~~~~~~~~~~~~~~~~~~~~

extern map *student_map;

/**
    Run once at program start. Calls functions from other modules to do the following.

    @note (1) - Create an initial user data file if it doesn't exist
    @note (2) - Initialize the students array.
    @note (3) - Initialize the students map.
    @note (4) - Read the data from the user data file into the map/array.
    @note (5) - Initializes the shared memory segment.
    @return The ID of the shared memory segment. If -1, there was an error.
*/
int Initialize();

/**
    Called repeatedly with a delay.

    @note (1) - Sets all users to inactive.
    @note (2) - Reads the result of the `who` command, setting some users to active, and possibly changing 'dirty' and last login times.
    @note (3) - Overwrites the user data file if we are dirty.
    @note (4) - Sets dirty to false.
    @note (5) - Re-writes the shared memory.

    @param shm_id The ID of the shared memory segment.

*/
void Process(int shm_id);

/**
    Clears / Deallocates the shared virtual memory segment.

    @note To execute the command, pass "clear" as an argument to the program.
*/
void ClearCommand();

/**
    Deletes and re-creates the static-user-data file and cumulative login file.

    @note To execute the command, pass "reset" as an argument to the program.
    @warning This will clear login times.
*/
void ResetCommand();


/**
    Stops an existing server process if it is running.

    @note To execute the command, pass "stop" as an argument to the program.
    @todo Actually stop the server.
*/
void StopCommand();

/**
    If a server exists, stops it. Begins the process loop.

    @todo Stop existing server.
    @note To execute the command, pass "run" as an argument to the program.
*/
void RunCommand();

/**
    Displays the commands available to the user.

    @note To execute the command, pass "help" as an argument to the program.
    @note This command will also run if arg num is incorrect or if invalid option is entered.
    @todo colors?
*/
void HelpCommand();


#endif

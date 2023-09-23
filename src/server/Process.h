#ifndef Process_h
#define Process_h
/*
    This module handles the processes that this server might execute. It calls functions from the other modules to realize program changes.
*/
#include "map.h"

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

#endif
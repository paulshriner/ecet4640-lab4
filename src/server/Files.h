#ifndef Files_H
#define Files_H

#include "Data.h"

/**
    When the program is first run, it will create two initial files.

    `initial-cumulative.txt` contains the result of running "ac -p" to get the total login time (in float minutes) of each user.

    `last-login.txt` contains all logins as unix timestamp 0, initially. They will then be updated / overwritten as the process runs

    @todo initial-cumulative.txt

*/


/*
    File name for the last login times that will be used
*/
#define LOGIN_TIMES_FILE "last-login.txt"

/**
 * Creates the initial `last-login.txt` file.
 * 
 * Each line contains:
 * - The ID from the students array, where the line # - 1 = the index of the students array
 * - A tab character
 * - A 0
 * - A newline
 * 
 * @returns A 0 if the operation was succesful, otherwise nonzero.
*/
int CreateInitialLoginTxt();


/**
    Dumps last Login times, overwriting the values in `last-login.txt`. 

 * Each line contains:
 * - The ID from the students array, where the line # - 1 = the index of the students array
 * - A tab character
 * - A number, represneting the unix timestamp of the last opened time.
 * - A newline
 * @param students A pointer to the DATA_NUM_RECORDS length student array that will be read to retreive login times.
 * @returns A 0 if the operation was succesful, otherwise a nonzero.
*/
int DumpLoginTimes(Student* students);

#endif 
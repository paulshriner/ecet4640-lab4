#ifndef Files_H
#define Files_H

#include "Data.h"
#include "map.h"

/**
    When the program is first run, it will create two initial files.

    `initial-cumulative.txt` contains the result of running "ac -p" to get the total login time (in float minutes) of each user.

    `last-login.txt` contains all logins as unix timestamp 0, initially. They will then be updated / overwritten as the process runs

    @todo initial-cumulative.txt

*/

// ---------------------------------------------------------------
//              last-login operations
// ---------------------------------------------------------------

/*
    File name for the text file that will store last login times.
*/
#define LOGIN_TIMES_FILE "last-login.txt"

/**
 * @brief Determines whether a file exists.
 * @returns 1 if it exists. 0 if it does not.
*/
short FileExists(char * file_name_to_check);

/**
 * @brief Creates the initial last logins file. This should be called only the first time the program runs, if it doesn't exist.
 * @param file_name The file name to create.
 * @param id_list An array containing the IDs. Eg. "Data_IDs" from Data.h
 * @param id_list_len The length of the id_list. Eg. "DATA_NUM_RECORDS" from Data.h
 * 
 * @note Each line contain in the created `last-login.txt` file contains: 
 * @note (1) The ID from the students array, where the `line # - 1` == the index of the students array 
 * @note (2) A tab character 
 * @note (3) A '0' 
 * @note (4) A newline.
 * @note The order of entries in the file is the same as the order in the Data_IDs array from Data.c.
 * 
 * @returns A 0 if the operation was succesful, otherwise nonzero.
*/
int CreateInitialLoginTxt(char * file_name, char ** id_list, int id_list_len);

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

/**
 * @brief Fills a map such that key of user_id maps to a time_t, using the data from the login-times .txt file.
 * @param student_map The map of student structs to be populated from the login.txt file
 * @param file_name The name of the login.txt file.
 * @param id_list An array containing the IDs. Eg. "Data_IDs" from Data.h
 * @param id_list_len The length of the id_list. Eg. "DATA_NUM_RECORDS" from Data.h
 * @returns 0 if succesful, 1 if there was an error.
*/
int FillLoginMapFromFile( map* student_map, char * file_name, char ** id_list, int id_list_len); 

#endif 
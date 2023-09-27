#ifndef Files_H
#define Files_H
/**
 * @brief Definitions for functions that operate on files.
 */
#include "Data.h"
#include "map.h"

/**
 *
    Some program data needs to be stored in files, to preserve it in the case of early termination.

    There are two files that are created if they don't exist when the program is first run. One has userIDs linked to their age, gpa, and last login time. The other has userIDs linked to the cumulative login time as determined by `ac -p` in order to determine the time logged in since program first ran.
*/

/**
    File name for the text file that will store user data, namely, the age, gpa, and last login time.

     @note Each line contain in the created file contains:
     @note (1) The ID from the students array, where the `line # - 1` == the index of the students array
     @note (2) A tab character
     @note (3) A random int between 18 and 22, for the age.
     @note (4) A tab character
     @note (5) A random float between 2.5 and 4.0, for the GPA.
     @note (6) A tab character.
     @note (7) A 0 (representing the last login time)
     @note (8) A newline.
     @note The order of entries in the file is the same as the order in the Data_IDs array from Data.c.

*/
#define STATIC_USER_DATA_FILE "static-user-data.txt"

/**
   File name for the text file that will store the cumulative login time for each user at the point in time when it was created.

   The values in this file are subtracted from the result of running 'ac -p' later to get the cumulative time each user was logged in since the server started.
*/
#define STATIC_USER_CUMULATIVE_FILE "static-user-cumulative-start.txt"

/**
 * @brief Determines whether a file exists.
 * @returns 1 if it exists. 0 if it does not.
 */
short FileExists(char *file_name_to_check);

/**
    @brief Creates the initial user data file. This should be called only the first time the program runs, if it doesn't exist.

    @param file_name The file name to create.
    @param id_list An array containing the IDs. Eg. "Data_IDs" from Data.h
    @param id_list_len The length of the id_list. Eg. "DATA_NUM_RECORDS" from Data.h

    @returns A 0 if the operation was succesful, otherwise nonzero.
 */
int CreateInitialUserDataFile(char *file_name, char **id_list, int id_list_len);

/**
    @brief Writes the student array to the file.

    @param students A pointer to the student array that will be read into the file.
    @param arr_len The length of the students array. e.g. DATA_NUM_RECORDS from Data.h.
    @param file_name The file name to write.

    @returns A 0 if the operation was succesful, otherwise a nonzero.
*/
int WriteStudentArrayToFile(Student *students, int arr_len, char *file_name);

/**
    @brief Fills the student map with data from the file. It gets age, gpa, and lastLogin from this file.

    @param student_map The map of student structs to be populated from the login.txt file
    @param file_name The name of the login.txt file.
    @param id_list An array containing the IDs. Eg. "Data_IDs" from Data.h
    @param id_list_len The length of the id_list. Eg. "DATA_NUM_RECORDS" from Data.h

    @returns 0 if succesful, 1 if there was an error.
 */
int FillStudentMapFromFile(map *student_map, char *file_name, char **id_list, int id_list_len);

/**
   Creates the initial cumulative login time file.

   It will hold the result of running 'ac -p'.

   @param file_name The name of the file to created. EG STATIC_USER_CUMULATIVE_FILE
   @warning This file should already be validated to not exist.
   @returns 0 if succesful, -1 if the file couldn't be opened, -2 if the pipe couldn't be opened, otherwise an error code.
*/
int CreateInitialCumulativeFile(char *file_name);

#endif
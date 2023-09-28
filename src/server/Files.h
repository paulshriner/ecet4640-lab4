#ifndef Files_H
#define Files_H
/**
 * \defgroup Files
 * @brief The Files module contains functions which operate on files.
 * @details Some program data needs to be stored in files, to preserve it in the case of early termination.

    There are three files that are created if they don't exist when the program is first run. 
    
    - STATIC_USER_DATA_FILE contains a list of userIDs, ages, gpa, and last login time. Age and gpa are randomly generated on server start and when "reset" is run. The login time is updated when it changes as per the dirty flag.
    - STATIC_USER_CUMULATIVE_FILE contains the results of 'ac -p' run when the server first starts. These values will be subtracted from later pipes of "ac -p" to determine the cumulative time since the server started. 
    - LOCKFILE contains a flag, 0 or 1, that indicates whether the STATIC_USER_DATA_FILE has been re-randomized and should be re-read. It contains the process ID of the running server process. It serves as an indicator to the process as to whether a server is already running and, when "close" is passed as a command line argument, which process to kill.
    @{
 */
#include "Data.h"
#include "map.h"

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
   @note Each line contains the following.
   @note (1) A user ID
   @note (2) An integer representing the minutes the user has been logged in.
*/
#define STATIC_USER_CUMULATIVE_FILE "static-user-cumulative-start.txt"

/**
    The lockfile serves as a signal to subsequent processes as to whether or not server is already running.
    
    @note File contains the following
    @note (1) a 1 or a 0 indicating whether the data has been reset and must be re-read
    @note (2) an integer correcponding to the PID of the process so that server close can end that process

*/
#define LOCKFILE "/tmp/ecet-server.lock"

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
 * @}
*/

#endif
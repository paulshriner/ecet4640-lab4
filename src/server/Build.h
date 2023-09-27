#ifndef BUILD_H
#define BUILD_H
/**
 * @brief Declarations for functions that populate data structures.
 */

#include "Data.h"
#include "map.h"

// ~~~~~~~~  Data Structures ~~~~~~~~~

/**
   The underlying students array. Will be heap allocated with malloc, after PopulateStudents is called.

   Generally this array and its length are still passed around via parameters, to decouple as much as possible and enable simple testing and dummy data.
*/
extern Student *students;

/**
    Allocate and populate the Students array with data.
    @param studentIDs An array of student IDs.
    @param studentNames An array of student names.
    @param arsize The size of the array to allocate.
    @warning studentIDs and studentNames must both be arsize in length.
*/
void PopulateStudents(char **studentIDs, char **studentNames, int arsize);

/**
   Given a student array, populates a student map, where the student IDs are the key, and the values are pointers to the items in the array.
   @param map The map structure to populate.
   @param studentArr An array of student structures.
   @param studentArrLength The length of the students array.
 */
void BuildStudentMap(map *stmap, Student *studentArr, int studentArrLength);

// ~~~~~~~~  Processing ~~~~~~~~~

/** Set to '1' if there are changes that should be written to a file. */
extern short dirty;

/**
    Executes the 'who' command by reading from a file pipe. Calls ProcessWhoLine for each line, to realize updates in the user data from the who command.

    @param stmap The student map.
    @returns 0 if succesful, otherwise nonzero.
*/
int UpdateFromWho(map *stmap);

/**

    Processes a single line as read from the 'who' shell command. Uses that data to update the relevant student by retrieving them from the student map. Updates that students last login time. Also sets 'active' to 1 for the found student.

    @attention May set dirty to 1.

    @param stmap The student map.
    @param whoLine The line of text, such as returned from fgets
    @param whoLineLength The length of that text.

    @returns 0 if success, -1 if the student was not found in the map.

*/
int ProcessWhoLine(map *stmap, char *whoLine, int whoLineLength);

/**
    Sets the 'active' member on all students in the students array to 0.

    @param stud_arr The students array.
    @param arr_len The length of the students array.
*/
void SetAllStudentsInactive(Student *stud_arr, int arr_len);

/**
    Writes the students array to the location specified by mem_ptr (eg. the shared memory segment).

    @param mem_ptr The address to write at.
    @param stud_arr The students array to write.
    @param arr_len The length of the students array.

*/
void WriteStudentsToMemory(void *mem_ptr, Student *stud_arr, int arr_len);

// ~~~~~~~~  Cumulative Processing ~~~~~~~~~

/**
    Populates the cumulative map by reading from the initial cumulative file. The map will be of the form [userID] -> minutes_float

    The map will contain users who we don't care about, but it doesn't matter.
    @param cum_map A map of cumulative times. Different from the students map.
    @param filename The filename where the initial cumulative times are located.

    @returns 0 if success. -1 if it failed to find the file.
*/
int ReadInitialCumulative(map *time_map, char *filename);

/**
    Pipes ac -p, then calls ReadCumulativeLine to update the student map.

    @note After this runs, the student map cumulative will be their total login time in the system. This total time must be subtracted from the cumulative map time to find the time they have been logged in since the program started.

    @param st_map The students map.
    @returns 0 on success.
*/
int ReadACP(map *st_map);

/**
    Reads a single line from the initial cumulative file and updates the map so that userID maps to a float value in the initial file.

    @note A line is structured like this: `	mes08346                            10.06`
    It finishes with a line starting with `total `; this line should be disregarded.
    @param cum_map The cumulative map.
    @param acp_line A single line from ac -p.
    @returns -1 ...
*/
void ReadCumulativeFileLine(map *cum_map, char *acp_line);

/**
    Reads a single line from the result of ac -p into the students map.

    @param stmap A map of students.
    @param acp_line A string representing 1 line result from ac -p.
    @returns -1 if acp_line is NULL or length is less than 1, otherwise 0.
*/
int ReadAcpPipeLine(map *stmap, char *acp_line);

/**
    Calculates the cumulative time for each student by subtracting map[studentID] from student.loginDuration.

    @warning student.loginDuration must have already been set to the total cumulative time logged in.

    @param stud_arr The student's array.
    @param arr_len The length of students array.
    @param cum_map A map mapping studentIds to their cumulative login time when the server was started.
*/
void CalculateCumulative(Student *stud_arr, int stud_arr_len, map *cum_map);

#endif
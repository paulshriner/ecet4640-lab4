#ifndef BUILD_H
#define BUILD_H

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

#endif
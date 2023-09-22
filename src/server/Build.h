#ifndef BUILD_H
#define BUILD_H

#include "Data.h"
#include "map.h"

/** 
   The underlying students array. Will be heap allocated with malloc, after PopulateStudents is called.
*/
extern Student* students;

/**
    Allocate and populate the Students array with data.
    @param studentIDs An array of student IDs.
    @param studentNames An array of student names.
    @param arsize The size of the array to allocate.
    @warning studentIDs and studentNames must both be arsize in length.
*/
void PopulateStudents(char ** studentIDs, char ** studentNames, int arsize);

/**
 * Given a student array, populates a student map, where the student IDs are the key, and the values are pointers to the items in the array.
 * @param map The map structure to populate.
 * @param studentArr An array of student structures.
 * @param studentArrLength The length of the students array.
*/
void BuildStudentMap(map* stmap, Student * studentArr, int studentArrLength);


/*
    Creates Shared Memory and Populates it with data
    @returns a number if unsuccesful (probably -1) or 0 if succesful
*/
int CreateAndPopulate();

/*
    Updates the last login times of students and the active state of the student structure
*/
void UpdateActive();

/*
    Calculates total time user has been logged in for and returns time in seconds
*/
int GetLoginTime(char* user);


#endif
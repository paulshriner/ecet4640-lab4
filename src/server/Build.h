#ifndef BUILD_H
#define BUILD_H

#include "Data.h"

/** 
   The students array that will be populated. 
*/
extern Student students[];

/*
    Populate the Students array with data.
*/
void PopulateStudents();

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
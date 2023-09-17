#ifndef Student_h
#define Student_h

#include "Data.h"
#include <time.h>
#include <sys/types.h>

/*
    The size of one student record.
*/
#define DATA_SIZE 56

/*
    The student data type.
*/
typedef struct
{
    char userID[DATA_ID_MAX_LENGTH];
    char fullName[DATA_NAME_MAX_LENGTH];
    short age;
    float gpa;
    short active;
    time_t lastLogin;
    int loginDuration;
} Student;

#endif
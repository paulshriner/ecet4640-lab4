#include "Build.h"
#include "string.h"
#include <stdlib.h>

Student students[DATA_NUM_RECORDS];

/*
    Generates a random integer from min to max inclusively
*/
int randAge(int min, int max) {
    return rand() % (max - min + 1) + min;
}

//TODO build a generator for random floats

int PopulateStudents() {
    int i;
    for(i = 0; i < DATA_NUM_RECORDS; i++) {
        strcpy(students[i].userID, Data_IDs[i]);
        strcpy(students[i].fullName, Data_Names[i]);
        students[i].age = randAge(18, 22);
    }
}
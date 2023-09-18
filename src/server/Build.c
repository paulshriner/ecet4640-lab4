#include "Build.h"
#include "string.h"

Student students[DATA_NUM_RECORDS];

int PopulateStudents() {
    int i;
    for(i = 0; i < DATA_NUM_RECORDS; i++) {
        strcpy(students[i].userID, Data_IDs[i]);
    }
}
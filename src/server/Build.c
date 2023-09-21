#include "Build.h"
#include "memShare.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>

Student students[DATA_NUM_RECORDS];

/*
    Generates a random integer from min to max inclusively
*/
int randAge(int min, int max) {
    return rand() % (max - min + 1) + min;
}

//TODO build a generator for random floats

void PopulateStudents() {
    int i;
    for(i = 0; i < DATA_NUM_RECORDS; i++) {
        strcpy(students[i].userID, Data_IDs[i]);
        strcpy(students[i].fullName, Data_Names[i]);
        students[i].age = randAge(18, 22);
    }
}

int CreateAndPopulate() {
    int shm_id = CreateSharedMemory();
    if(shm_id < 0) {
        return shm_id;
    }

    PopulateStudents();
    void * mem_pt = GetMemoryPointer(shm_id);
    FillSharedMemory(mem_pt, students, DATA_NUM_RECORDS);
    int err = ReleaseMemoryPointer(mem_pt);
    if (err) {
        return err;
    }

    return 0;
}

int UpdateLastLogin(/*Map Struct*/) {
    char command[20] = "who";
    char result[1024] = {0x0};
    
    FILE* fpipe;
    
    if (0 == (fpipe = (FILE*)popen(command, "r"))) {
        perror("Failed to run %s, could not gather time");
        return -1;
    }


    while (fgets(result, sizeof(result), fpipe) != NULL) {
        int i;
        for(i = 0; i < DATA_NUM_RECORDS; i++) {
            if(strncmp(result, Data_IDs[i], strlen(Data_IDs[i]) == 0)) {
                time_t last_login = ParseStudentLoginTime(result);
                // update map
                break;
            }
        }
    }
    
    return 0;
}

time_t ParseLoginTime(char* raw_string) {
    int i = 0;
    char c = raw_string[i];
    /* shr5683  pts/0        2023-09-21 15:27 (10.2.9.12)*/
    while(c != ' ') { //skips id
        c = raw_string[++i];
    }
    while(c == ' ') {
        c = raw_string[++i];
    }
    while(c != ' ') { //skips pts
        c = raw_string[++i];
    }
    while(c == ' ') {
        c = raw_string[++i];
    } //now at year
    
}

//shr5683  pts/0        2023-09-21 15:27 (10.2.9.12)
//	mes08346                            10.06
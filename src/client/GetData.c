#include "GetData.h"
#include <sys/shm.h>

Student students_client[DATA_NUM_RECORDS];

int FillStudentsFromMemory() {
    int shid = shmget(0x727, sizeof(students_client), SHM_RDONLY);
    void * mp = shmat(shid, NULL, SHM_RDONLY);
    int i = 0;
    while(i < DATA_NUM_RECORDS) {
        Student * s = (Student *)(mp + sizeof(Student)*i);
        students_client[i] = *s;
        i++;
    }
    return 0;
}
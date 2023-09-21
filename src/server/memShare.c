#include "memShare.h"
#include <string.h>
#include <stdio.h>

/*
    Todo: Error handling and printing
*/

int CreateSharedMemory()
{
    return shmget(MEM_KEY, MEM_SIZE, IPC_CREAT | MEM_PERMISSIONS);
}

int DestroySharedMemory()
{
    int shm_id = shmget(MEM_KEY, MEM_SIZE, 0);
    int control_result = shmctl(shm_id, IPC_RMID, 0);
    if(control_result != -1) return 0;
    return control_result;
}

void * GetMemoryPointer(int shared_mem_id)
{
    return shmat(shared_mem_id, NULL, 0);
}

int ReleaseMemoryPointer(void *shmaddr) {
    return shmdt(shmaddr);
}

void FillSharedMemory(void * shared_memory, Student* students_arr, int arr_length) {
    int i; //TODO figure out a way to check if this will error. Otherwise this function should be made into a void
    Student* s_mem = (Student*) shared_memory;
    for(i = 0; i < arr_length; i++) {
        strcpy(s_mem[i].userID, students_arr[i].userID);
        strcpy(s_mem[i].fullName, students_arr[i].fullName);
        s_mem[i].age = students_arr[i].age;
        s_mem[i].gpa = students_arr[i].age;
        s_mem[i].active = students_arr[i].active;
        s_mem[i].lastLogin = students_arr[i].lastLogin;
        s_mem[i].loginDuration = students_arr[i].loginDuration;
    }
}
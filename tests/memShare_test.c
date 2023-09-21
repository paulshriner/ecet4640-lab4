#include "memShare_test.h"
#include "Data.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>

void DestroyMem(CuTest * tc)
{
    int dest_result = DestroySharedMemory();
    CuAssertIntEquals_Msg(tc, "destroy result not -1", 1, dest_result != -1);
    dest_result = DestroySharedMemory();
    CuAssertIntEquals_Msg(tc, "destroy result -1 on double destroy", 1, dest_result == -1);
}

void testCreateDestroy(CuTest *tc)
{
    int shm_id = CreateSharedMemory();
    CuAssertIntEquals_Msg(tc, "Shm ID not -1", 1, shm_id != -1);
    DestroyMem(tc);
}

void testAttachDestroy(CuTest *tc)
{
    int shm_id = CreateSharedMemory();
    void* z;
    z = GetMemoryPointer(shm_id);
    CuAssertIntEquals_Msg(tc, "\nPointer result from shmat not (void*) -1", 1, z != (void*)-1 );
    ReleaseMemoryPointer(z);
    DestroyMem(tc);
}

void testFillMem(CuTest* tc) 
{
    int shm_id = CreateSharedMemory();

    Student arr[3];

    strcpy(arr[0].userID, "testID");
    strcpy(arr[0].fullName, "Test Name");
    arr[0].age = 1;
    arr[0].gpa = 1.7;
    arr[0].active = 0;
    arr[0].lastLogin = time(NULL);
    arr[0].loginDuration = 7;

    strcpy(arr[1].userID, "testID1");
    strcpy(arr[1].fullName, "Test Nam1");
    arr[1].age = 2;
    arr[1].gpa = 2.5;
    arr[1].active = 1;
    arr[1].lastLogin = time(NULL);
    arr[1].loginDuration = 22;

    strcpy(arr[2].userID, "testID2");
    strcpy(arr[2].fullName, "Test Name2");
    arr[2].age = 3;
    arr[2].gpa = 3.3;
    arr[2].active = -1;
    arr[2].lastLogin = time(NULL);
    arr[2].loginDuration = -10;

    FillSharedMemory(GetMemoryPointer(shm_id), arr, 3);

    // CuAssertIntEquals_Msg(tc, "Filling Memory Failed", 1, r == 0);
    DestroyMem(tc);
}

CuSuite *MemshareGetSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testCreateDestroy);
    SUITE_ADD_TEST(suite, testAttachDestroy);
    return suite;
}
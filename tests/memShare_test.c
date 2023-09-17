#include "memShare_test.h"

void testCreateDestroy(CuTest *tc)
{
    int shm_id = CreateSharedMemory();
    CuAssertIntEquals_Msg(tc, "Shm ID not -1", 1, shm_id != -1);
    shm_id = CreateSharedMemory();
    CuAssertIntEquals_Msg(tc, "Shm ID is -1 on double create", 1, shm_id == -1);
    int dest_result = DestroySharedMemory();
    CuAssertIntEquals_Msg(tc, "destroy result not -1", 1, dest_result != -1);
    dest_result = DestroySharedMemory();
    CuAssertIntEquals_Msg(tc, "destroy result -1 on double destroy", 1, dest_result == -1);
}

CuSuite *MemshareGetSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testCreateDestroy);
    return suite;
}
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

CuSuite *MemshareGetSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testCreateDestroy);
    SUITE_ADD_TEST(suite, testAttachDestroy);
    return suite;
}

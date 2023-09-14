#include "Student_test.h"
#include "Student.h"

void testDataSize(CuTest *tc) {
    CuAssertIntEquals_Msg(tc, "The size of the data size should be as expected", DATA_SIZE, sizeof(Student));
}

CuSuite* studentDataGetSuite() {
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testDataSize);
    return suite;
}
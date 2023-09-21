#include "Build_test.h"

void t1(CuTest * tc) {

}

CuSuite *BuildGetSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, t1);
    return suite;
}
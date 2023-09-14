#include "main_util_test.h"

#include "CuTest.h"
#include "main_util.h"

void testSquare(CuTest *tc) {
    int t_val = 1;
    CuAssertIntEquals_Msg(tc, "1*1=1", 1, square(t_val));
    CuAssertIntEquals_Msg(tc, "-1*-1=1", 1, square(-1));
    CuAssertIntEquals_Msg(tc, "2*2=4", 4, square(2));
    CuAssertIntEquals_Msg(tc, "-2*-2=-4", 4, square(-2));
}


CuSuite *mainUtilGetSuite() {
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testSquare);
    return suite;
}
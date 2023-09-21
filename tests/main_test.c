#include "CuTest.h"
#include "Student_test.h"
#include "memShare_test.h"
#include "Build_test.h"
#include <stdio.h>

void RunAllTests(void)
{
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    CuSuiteAddSuite(suite, studentDataGetSuite());
    CuSuiteAddSuite(suite, MemshareGetSuite());
    CuSuiteAddSuite(suite, BuildGetSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}

int main(void)
{
    RunAllTests();
}
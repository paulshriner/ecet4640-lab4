#include "CuTest.h"
#include "util_test.h"
#include "Student_test.h"
#include "memShare_test.h"
#include "Build_test.h"
#include "map_test.h"
#include "hash_test.h"
#include "File_test.h"
#include <stdio.h>

void RunAllTests(void)
{
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    CuSuiteAddSuite(suite, utilTestGetSuite());
    CuSuiteAddSuite(suite, studentDataGetSuite());
    CuSuiteAddSuite(suite, MemshareGetSuite());
    CuSuiteAddSuite(suite, BuildGetSuite());
    CuSuiteAddSuite(suite, hashTestGetSuite());
    CuSuiteAddSuite(suite, mapTestGetSuite());
    CuSuiteAddSuite(suite, filesGetSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    return 0;
}

int main(void)
{
    RunAllTests();
}
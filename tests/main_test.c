#include "CuTest.h"
#include "main_util_test.h"
#include <stdio.h>

void RunAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite * suite = CuSuiteNew();

    CuSuiteAddSuite(suite, mainUtilGetSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output -> buffer);
}

int main(void) {
    RunAllTests();
}
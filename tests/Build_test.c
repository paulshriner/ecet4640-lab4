#include "Build_test.h"
#include "Data.h"
#include <stdlib.h>

void testBuildMap(CuTest * tc) {
    PopulateStudents(Data_IDs, Data_Names, DATA_NUM_RECORDS);
    map * smap = NewMap(50);
    BuildStudentMap(smap, students, DATA_NUM_RECORDS);
    int i;
    for(i = 0; i < DATA_NUM_RECORDS; i++) {
        map_result result = Map_Get(smap, Data_IDs[i]);
        CuAssertIntEquals_Msg(tc, "should have result for each id", 1, result.found);
        Student * sp = (Student*) (result.data);
        CuAssertStrEquals_Msg(tc, "each student should have their key the same as the student id", Data_IDs[i], sp->userID);
        CuAssertStrEquals_Msg(tc, "each student should have their full name set correctly w the associated ID", Data_Names[i], sp->fullName);
        CuAssertPtrEquals_Msg(tc, "each data in the map should be the corresponding entry in the array", &students[i], sp);
    }
    map_result result = Map_Get(smap, "random fake id");
    CuAssertIntEquals_Msg(tc, "should not have a result for a random string", 0, result.found);
    free(smap);
    free(students);
}

CuSuite *BuildGetSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testBuildMap);
    return suite;
}
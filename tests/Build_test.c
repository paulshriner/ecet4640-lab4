#include "Build_test.h"
#include "Data.h"
#include <stdlib.h>
#include <string.h>

void testBuildMap(CuTest *tc)
{
    PopulateStudents(Data_IDs, Data_Names, DATA_NUM_RECORDS);
    map *smap = NewMap(50);
    BuildStudentMap(smap, students, DATA_NUM_RECORDS);
    int i;
    for (i = 0; i < DATA_NUM_RECORDS; i++)
    {
        map_result result = Map_Get(smap, Data_IDs[i]);
        CuAssertIntEquals_Msg(tc, "should have result for each id", 1, result.found);
        Student *sp = (Student *)(result.data);
        CuAssertStrEquals_Msg(tc, "each student should have their key the same as the student id", Data_IDs[i], sp->userID);
        CuAssertStrEquals_Msg(tc, "each student should have their full name set correctly w the associated ID", Data_Names[i], sp->fullName);
        CuAssertPtrEquals_Msg(tc, "each data in the map should be the corresponding entry in the array", &students[i], sp);
    }
    map_result result = Map_Get(smap, "random fake id");
    CuAssertIntEquals_Msg(tc, "should not have a result for a random string", 0, result.found);
    free(smap);
    free(students);
}

void testProcessWho(CuTest *tc)
{
    PopulateStudents(Data_IDs, Data_Names, DATA_NUM_RECORDS);
    map *smap = NewMap(50);
    BuildStudentMap(smap, students, DATA_NUM_RECORDS);
    char *line = "shr5683  pts/0        2023-09-21 15:27 (10.2.9.12)";
    ProcessWhoLine(smap, line, strlen(line));
    line = "bol4559  pts/1        2023-09-21 14:26 (158.83.17.48)";
    ProcessWhoLine(smap, line, strlen(line));
    line = "mil7233  pts/2        2023-09-21 16:44 (10.2.89.69)";
    ProcessWhoLine(smap, line, strlen(line));
    line = "mes08346 pts/5        2023-09-21 16:18 (10.2.89.68)";
    ProcessWhoLine(smap, line, strlen(line));

    map_result result = Map_Get(smap, "shr5683");
    Student *student = (Student *)result.data;
    CuAssertIntEquals_Msg(tc, "should exist in map", 1, result.found);
    CuAssertIntEquals_Msg(tc, "timestamp should be processed correctly", 1695324420L, student->lastLogin);
    CuAssertIntEquals_Msg(tc, "student should be set to active", 1, student->active);

    result = Map_Get(smap, "bol4559");
    student = (Student *)result.data;
    CuAssertIntEquals_Msg(tc, "should exist in map", 1, result.found);
    CuAssertIntEquals_Msg(tc, "timestamp should be processed correctly", 1695320760L, student->lastLogin);
    CuAssertIntEquals_Msg(tc, "student should be set to active", 1, student->active);

    result = Map_Get(smap, "mil7233");
    student = (Student *)result.data;
    CuAssertIntEquals_Msg(tc, "should exist in map", 1, result.found);
    CuAssertIntEquals_Msg(tc, "timestamp should be processed correctly", 1695329040L, student->lastLogin);
    CuAssertIntEquals_Msg(tc, "student should be set to active", 1, student->active);

    result = Map_Get(smap, "mes08346");
    student = (Student *)result.data;
    CuAssertIntEquals_Msg(tc, "should exist in map", 1, result.found);
    CuAssertIntEquals_Msg(tc, "timestamp should be processed correctly", 1695327480L, student->lastLogin);
    CuAssertIntEquals_Msg(tc, "student should be set to active", 1, student->active);

    free(smap);
    free(students);
}

CuSuite *BuildGetSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testBuildMap);
    SUITE_ADD_TEST(suite, testProcessWho);
    return suite;
}
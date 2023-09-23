#include "File_test.h"
#include "map.h"
#include "Data.h"
#include "Build.h"
#include "time.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void testCreateUserFile(CuTest *tc)
{
    char *tfn = "_test-user-file.txt";
    int ex = FileExists(tfn);
    CuAssertIntEquals_Msg(tc, "Test file should not exist on test start", 0, ex);
    ex = CreateInitialUserDataFile(tfn, Data_IDs, DATA_NUM_RECORDS);
    CuAssertIntEquals_Msg(tc, "There should not be errors creating the initial file.", 0, ex);
    ex = FileExists(tfn);
    CuAssertIntEquals_Msg(tc, "The file should exist after CreateInitialLoginTxt called.", 1, ex);

    map *studMap = NewMap(50);
    PopulateStudents(Data_IDs, Data_Names, DATA_NUM_RECORDS);
    BuildStudentMap(studMap, students, DATA_NUM_RECORDS);
    FillStudentMapFromFile(studMap, tfn, Data_IDs, DATA_NUM_RECORDS);
    int i;
    for (i = 0; i < DATA_NUM_RECORDS; i++)
    {
        map_result result = Map_Get(studMap, Data_IDs[i]);
        CuAssertIntEquals_Msg(tc, "each id should be found", 1, result.found);
        Student *data = (Student *)result.data;
        CuAssertIntEquals_Msg(tc, "each student should have 0 login time", 0, data->lastLogin);
    }
    free(studMap);
    free(students);
    remove(tfn);
}

void testUpdateUserFile(CuTest *tc)
{
    char *tfn = "_test-user-file-2.txt";
    int ex = FileExists(tfn);
    CuAssertIntEquals_Msg(tc, "Test file should not exist on test start", 0, ex);
    PopulateStudents(Data_IDs, Data_Names, DATA_NUM_RECORDS);
    int newAges[DATA_NUM_RECORDS];
    time_t newTimes[DATA_NUM_RECORDS];
    int i;
    // populate some random ages and last login times
    for (i = 0; i < DATA_NUM_RECORDS; i++)
    {
        newAges[i] = RandomInteger(0, 1000);
        newTimes[i] = (long)RandomInteger(0, 10000);
        students[i].age = newAges[i];
        students[i].lastLogin = newTimes[i];
    }
    WriteStudentArrayToFile(students, DATA_NUM_RECORDS, tfn);
    free(students);
    PopulateStudents(Data_IDs, Data_Names, DATA_NUM_RECORDS);
    map *stumap = NewMap(100);
    BuildStudentMap(stumap, students, DATA_NUM_RECORDS);
    FillStudentMapFromFile(stumap, tfn, Data_IDs, DATA_NUM_RECORDS);
    for (i = 0; i < DATA_NUM_RECORDS; i++)
    {
        CuAssertIntEquals_Msg(tc, "age should have been saved to file", newAges[i], students[i].age);
        CuAssertIntEquals_Msg(tc, "time should have been saved to file", 1, students[i].lastLogin == newTimes[i]);
    }
    free(students);
    remove(tfn);
}

CuSuite *filesGetSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testCreateUserFile);
    SUITE_ADD_TEST(suite, testUpdateUserFile);
    return suite;
}

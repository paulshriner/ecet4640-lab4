#include "File_test.h"
#include "map.h"
#include "Data.h"
#include "Build.h"
#include "time.h"

void testLoginCreateAndMapParse(CuTest *tc) {
    char * tfn = "_test-login.txt";
    int ex = FileExists(tfn);
    CuAssertIntEquals_Msg(tc, "Test file should not exist on test start", 0, ex);
    ex = CreateInitialLoginTxt(tfn, Data_IDs, DATA_NUM_RECORDS);
    CuAssertIntEquals_Msg(tc, "There should not be errors creating the initial file.", 0, ex);
    ex = FileExists(tfn);
    CuAssertIntEquals_Msg(tc, "The file should exist after CreateInitialLoginTxt called.", 1, ex);

    map * studMap = NewMap(50);
    PopulateStudents(Data_IDs, Data_Names, DATA_NUM_RECORDS);
    BuildStudentMap(studMap, students, DATA_NUM_RECORDS);
    FillLoginMapFromFile(studMap, tfn, Data_IDs, DATA_NUM_RECORDS);
    int i;
    for(i = 0; i < DATA_NUM_RECORDS; i++) {
        map_result result = Map_Get(studMap, Data_IDs[i]);
        CuAssertIntEquals_Msg(tc, "each id should be found", 1, result.found);
        Student * data = (Student *) result.data;
        CuAssertIntEquals_Msg(tc, "each student should have 0 login time", 0, data->lastLogin);
    }

    remove(tfn);

}

CuSuite *filesGetSuite() {
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testLoginCreateAndMapParse);
    return suite;
}

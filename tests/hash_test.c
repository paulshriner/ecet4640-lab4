#include "hash_test.h"

#include "CuTest.h"
#include "map.h"
#include "string.h"
#include "stdio.h"

void testHashLog(CuTest *tc)
{
    int result = hash_log2(3);
    CuAssertIntEquals(tc, 2, result);
    result = hash_log2(4);
    CuAssertIntEquals(tc, 3, result);
    result = hash_log2(5);
    CuAssertIntEquals(tc, 3, result);
}

void testHashStrings(CuTest *tc)
{
    char *to_test[] = {"a", "ab",
                       "b", "c", "f", "abx", "asdfasd", "advas", "13dfajm", "0-123m,", "asdfas", "iojnopkm", "jhiuasdbf", "aaf23214", "amasdfav", "1`1231245", "amsfasv", "yAEAEDWR", "masdfav c", "14mavf", "1345mkmac", "1`41mvac", "125rmjpa", "1j54p123m,a", "asdofjnaqsdf", "asfda", "asdfva", "asdfasdjmfm", "akp[k[pk143]]"};
    int arsize = (int)(sizeof(to_test) / sizeof(char *));

    int log_ars = hash_log2(arsize);
    int alloc_size = hash_upperLimit(log_ars);

    int results[alloc_size];
    int i, misses = 0;
    for (i = 0; i < alloc_size; i++)
    {
        results[i] = 0;
    }
    for (i = 0; i < arsize; i++)
    {
        int len = strlen(to_test[i]);
        int result = hash_string(alloc_size, to_test[i], len);
        // printf("String %s hashed to %d.\n", to_test[i], result);
        if (results[result] != 0)
        {
            misses++;
            results[result] += 1;
        }
        else
        {
            results[result] = 1;
        }
    }
    CuAssertIntEquals_Msg(tc, "Should be few misses", misses < 10, 1);
}

CuSuite *hashTestGetSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testHashLog);
    SUITE_ADD_TEST(suite, testHashStrings);
    return suite;
}
#include <stdio.h>
#include "Print.h"

#include "GetData.h"

int main()
{
    FillStudentsFromMemory();
    int i = 0;
    PrintStudentRowHeader();
    while(i < DATA_NUM_RECORDS) {
        PrintStudentRow(&students_client[i]);
        i++;
    }
    return 0;
}
#include "Print.h"
#include "colors.h"
#include <stdio.h>

void printActive(short active)
{
    if (active)
    {
        printf("%s%8s%s", BG_GREEN, "👍", COLOR_RESET);
    }
    else
    {
        printf("%s%8s%s", BG_RED, "👎", COLOR_RESET);
    }
}

void PrintStudentRow(Student *student)
{
    if (student == 0)
    {
        return;
    }
    printActive(student->active);
    printf("%*s", DATA_ID_MAX_LENGTH, student->userID);
    printf("%5d", student->age);
    printf("%*s  ", DATA_NAME_MAX_LENGTH, student->fullName);
    printf("%.2f", student->gpa);
    printf("%20s", "12/12/12 00:00:00");
    printf("%10s", "00:00:00");
    printf("\n");
}

void PrintStudentRowHeader()
{
    printf("%s", SET_UNDERLINE);
    printf("%7s", "active");
    printf("%*s", DATA_ID_MAX_LENGTH, "id");
    printf("%5s", "age");
    printf("%*s", DATA_NAME_MAX_LENGTH, "name");
    printf("%5s", "gpa");
    printf("%20s", "last login");
    printf("%10s", "duration");
    printf("%s\n", COLOR_RESET);
}

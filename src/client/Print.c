#include "Print.h"
#include "colors.h"
#include <stdio.h>
#include <sys/types.h>
#include <time.h>

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

    struct tm *tm;
    tm = localtime(&(student->lastLogin));
    short int mm = (short int)tm -> tm_mon;
    short int dd = (short int)tm -> tm_mday;
    short int yy = (short int)tm -> tm_year;
    short int hr = (short int)tm -> tm_hour;
    short int mn = (short int)tm -> tm_min;

    printActive(student->active);
    printf("%*s", DATA_ID_MAX_LENGTH, student->userID);
    printf("%5d", student->age);
    printf("%*s  ", DATA_NAME_MAX_LENGTH, student->fullName);
    printf("%.2f", student->gpa);
    if (student->lastLogin == 0) {
        printf("%18s ", "UNKNOWN");
    } else {
        printf("%5d/%d/%d %02d:%02d", 1 + mm, dd, 1900 + yy, hr, mn);
    }
    printf("%10d", student->loginDuration);
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

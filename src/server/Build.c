#include "Build.h"
#include "memShare.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// ~~~~~~~~  Data Structures ~~~~~~~~~

Student *students;

void PopulateStudents(char **studentIDs, char **studentNames, int arsize)
{
    students = malloc(sizeof(Student) * arsize);
    int i;
    for (i = 0; i < arsize; i++)
    {
        strcpy(students[i].userID, studentIDs[i]);
        strcpy(students[i].fullName, studentNames[i]);
        // students[i].age = randAge(18, 22);
    }
}

void BuildStudentMap(map *stmap, Student *studentArr, int studentArrLength)
{
    int i;
    for (i = 0; i < studentArrLength; i++)
    {
        Map_Set(stmap, studentArr[i].userID, (void *)(&studentArr[i]));
    }
}

// ~~~~~~~~  Processing ~~~~~~~~~

short dirty = 1; // start dirty

int UpdateFromWho(map *stmap)
{
    char command[4] = "who";
    char line[100];
    FILE *fpipe;
    fpipe = popen(command, "r");
    if (fpipe == NULL)
    {
        return -1;
    }

    while (fgets(line, sizeof(line), fpipe) != NULL)
    {
        ProcessWhoLine(stmap, line, strlen(line));
    }
    pclose(fpipe);

    return 0;
}

int ProcessWhoLine(map *stmap, char *whoLine, int whoLineLength)
{
    char userId[20];
    char dateString[50];
    char timeString[20];
    int read_total = 0;
    int read;
    sscanf(whoLine, " %s %n", userId, &read);
    read_total += read;

    map_result mr = Map_Get(stmap, userId);
    if (!mr.found)
    { // if we can't find that person in the map, return early
        return -1;
    }
    Student *student = (Student *)mr.data;

    sscanf(whoLine + read_total, " %s %n", dateString, &read); // will be thrown away. eg `pts/1'
    read_total += read;
    sscanf(whoLine + read_total, " %s %n", dateString, &read); // read the date string
    read_total += read;
    sscanf(whoLine + read_total, " %s %n", timeString, &read); // read the time string
    strcat(dateString, " ");
    strcat(dateString, timeString); // catenate the time string back to the date string

    time_t now = time(NULL);
    struct tm dtime = *localtime(&now);
    dtime.tm_sec = 0;

    memset(&dtime, 0, sizeof(struct tm));

    sscanf(dateString, "%d-%d-%d %d:%d", &(dtime.tm_year), &(dtime.tm_mon), &(dtime.tm_mday), &(dtime.tm_hour), &(dtime.tm_min));

    dtime.tm_year -= 1900;
    dtime.tm_mon -= 1;
    dtime.tm_hour -= 1;

    time_t parsed_time = mktime(&dtime);

    if (student->lastLogin != parsed_time)
    {
        student->lastLogin = parsed_time;
        dirty = 1;
    }
    student->active = 1;
    return 0;
}

void SetAllStudentsInactive(Student *stud_arr, int arr_len)
{
    int i;
    for (i = 0; i < arr_len; i++)
    {
        stud_arr[i].active = 0;
    }
}

void WriteStudentsToMemory(void *mem_ptr, Student *stud_arr, int arr_len)
{
    Student *memloc = (Student *)mem_ptr;
    int i;
    for (i = 0; i < arr_len; i++)
    {
        strcpy(memloc[i].userID, stud_arr[i].userID);
        strcpy(memloc[i].fullName, stud_arr[i].fullName);
        memloc[i].age = stud_arr[i].age;
        memloc[i].gpa = stud_arr[i].gpa;
        memloc[i].active = stud_arr[i].active;
        memloc[i].lastLogin = stud_arr[i].lastLogin;
        memloc[i].loginDuration = stud_arr[i].loginDuration;
    }
}

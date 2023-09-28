/**
 * \addtogroup Build
 * @{
 */
#include "Build.h"
#include "memShare.h"
#include "util.h"
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

int PipeWhoToStudentMap(map *stmap)
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

// ~~~~~~~~  Cumulative Processing ~~~~~~~~~

int ReadInitialCumulative(map *time_map, char *filename)
{
    FILE *file = fopen(filename, "r");
    char line[100];
    if (file == NULL)
    {
        return -1;
    }
    while (fgets(line, sizeof(line), file) != NULL)
    {
        ReadCumulativeFileLine(time_map, line);
    }

    fclose(file);
    return 0;
}

int PipeAcpToStudentMap(map *st_map)
{
    char command[6] = "ac -p";
    char line[300];
    FILE *fpipe;
    fpipe = popen(command, "r");
    if (fpipe == NULL)
    {
        return -1;
    }
    int err;
    while (fgets(line, sizeof(line), fpipe) != NULL)
    {
        err = ReadAcpPipeLine(st_map, line);
        if (err)
        {
            printf("\nError %d reading acp pipeline.", err);
            break;
        }
    }
    pclose(fpipe);
    return 0;
}

void ReadCumulativeFileLine(map *cum_map, char *acp_line)
{
    char userId[20];
    float hours;
    sscanf(acp_line, " %s %f ", userId, &hours);
    // int seconds = (int) (minutes * 60)
    long seconds = (long)(hours * 60 *60);
    // if(strcmp(userId, "mil7233") == 0) {
    //     printf("Cum file line for %s seconds = %ld\n", userId, seconds);
    // }
    Trim(userId);
    char* key = malloc( (strlen(userId)+1) * sizeof(char));
    strcpy(key, userId);
    Map_Set(cum_map, key, (void *)seconds);
}

int ReadAcpPipeLine(map *stmap, char *acp_line)
{
    if (acp_line == NULL || strlen(acp_line) < 1)
    {
        return -1;
    }
    char userId[40];
    float hours;
    sscanf(acp_line, "%s %f", userId, &hours);
    map_result result = Map_Get(stmap, userId);
    if (result.found)
    {
        Student *student = (Student *)result.data;
        int seconds = (int)(hours * 60*60);
        student->loginDuration = seconds;
        // if(strcmp(userId, "mil7233")==0) {
        //     printf("ACP pipe for %s student quant = %f\n", userId, hours);
        //     printf(" --- int seconds = %d\n", seconds);
        // }
    }
    return 0;
}


void CalculateCumulative(Student *stud_arr, int stud_arr_len, map *cum_map)
{
    int i;
    for (i = 0; i < stud_arr_len; i++)
    {
        map_result result = Map_Get(cum_map, stud_arr[i].userID);
        if (result.found)
        {
            
            long time_at_server_start = (long)result.data;
            stud_arr[i].loginDuration = stud_arr[i].loginDuration - time_at_server_start;
            // if(strcmp("mil7233", stud_arr->userID) == 0) {
            //     printf("calc cum: found user %s.\n", stud_arr[i].userID);
            //     printf(" tot time now: %ld\n", stud_arr[i].loginDuration);
            //     printf(" time at server start: %ld\n", time_at_server_start);
            //     printf(" new duration: %ld\n", stud_arr[i].loginDuration);
            // }
        }
    }
}
/**
 * @}
*/
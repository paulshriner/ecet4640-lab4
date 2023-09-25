#include "Files.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

short FileExists(char *file_name_to_check)
{
    FILE *file = fopen(file_name_to_check, "r");
    short result = 1;
    if (file == NULL)
    {
        result = 0;
    }
    else
    {
        fclose(file);
    }
    return result;
}

int CreateInitialUserDataFile(char *file_name, char **id_list, int id_list_len)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        return -1;
    }
    int i;
    for (i = 0; i < id_list_len; i++)
    {
        int rand_age = RandomInteger(18, 22);
        float gpa;
        if (RandomFlag(0.42))
        {
            gpa = 4.0; // 42% of the time, make the GPA 4.0
        }
        else
        {
            gpa = RandomFloat(2.5, 4.0);
        }
        fprintf(file, "%s\t%d\t%.2f\t%d\n", id_list[i], rand_age, gpa, 0);
    }
    fclose(file);
    return 0;
}

int FillStudentMapFromFile(map *student_map, char *file_name, char **id_list, int id_list_len)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        return -1;
    }
    // id buffer
    char user_id[9];
    int age;
    float gpa;
    long time;
    while (fscanf(file, "%9s\t%d\t%f\t%ld", user_id, &age, &gpa, &time) == 4)
    {
        map_result result = Map_Get(student_map, user_id);
        if (result.found == 0)
        {
            continue;
        }
        ((Student *)result.data)->age = age;
        ((Student *)result.data)->gpa = gpa;
        ((Student *)result.data)->lastLogin = time;
    }
    fclose(file);
    return 0;
}

int WriteStudentArrayToFile(Student *students, int arr_len, char *file_name)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        return -1;
    }
    int i;
    for (i = 0; i < arr_len; i++)
    {
        fprintf(file, "%s\t%d\t%.2f\t%ld\n", students[i].userID, students[i].age, students[i].gpa, students[i].lastLogin);
    }
    fclose(file);
    return 0;
}

int CreateInitialCumulativeFile(char * file_name) {
    FILE *file = fopen(file_name, "w");
    if(file == NULL) {
        return -1;
    }
    FILE *pipe = popen("ac -p", "r");
    if(pipe == NULL) {
        fclose(file);
        return -2;
    }

    char line[100];
    while(fgets(line, sizeof(line), pipe) != NULL) {
        fputs(line, file);
    }
    pclose(pipe);
    fclose(file);
    return 0;
}

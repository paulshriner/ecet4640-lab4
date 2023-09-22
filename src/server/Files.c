#include "Files.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

short FileExists(char * file_name_to_check) {
    FILE * file = fopen(file_name_to_check, "r");
    short result = 1;
    if(file == NULL) {
        result = 0;
    } else {
        fclose(file);
    }
    return result;
}

int CreateInitialLoginTxt(char * file_name, char ** id_list, int id_list_len) {
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        return -1;
    }
    int i;
    for(i = 0; i < id_list_len; i++) {
        fprintf(file, "%s\t0\n",id_list[i] );
    }
    fclose(file);
    return 0;
}

int FillLoginMapFromFile(map* student_map, char * file_name, char ** id_list, int id_list_len) {
    FILE * file = fopen(file_name, "r");
    if (file == NULL) {
        return -1;
    }
    // id buffer
    char line_buffer[9];
    long number;
    while(fscanf(file, "%9s\t%ld", line_buffer, &number)== 2) {
        map_result result = Map_Get(student_map, line_buffer);
        if(result.found == 0) {
            return -2;
        }
        ((Student*) result.data)->lastLogin = number;
    }
    fclose(file);
    return 0;

}
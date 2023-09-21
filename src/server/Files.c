#include "Files.h"
#include <stdlib.h>
#include <stdio.h>

int CreateInitialLoginTxt() {
    FILE* file = fopen(LOGIN_TIMES_FILE, "w");
    if (file == NULL) {
        return -1;
    }
    
    int i;
    for(i = 0; i < DATA_NUM_RECORDS; i++) {
        fprintf(file, "%s\t0\n",Data_IDs[i] );
    }

    return 0;
}
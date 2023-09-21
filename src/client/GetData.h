#ifndef GetData_H
#define GetData_H

#include "Data.h"

#define MEM_KEY_CLIENT 0x727

extern Student students_client[DATA_NUM_RECORDS];

int FillStudentsFromMemory();

#endif 
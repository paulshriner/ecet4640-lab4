#ifndef Data_h
#define Data_h

/*
    The total count of records.
*/
#define DATA_NUM_RECORDS 17
/*
    The amount of memory (bytes) required to be allocated for the ID field.
    Equal to the longest name in Data_IDs, "mes08346", plus the null terminator
*/
#define DATA_ID_MAX_LENGTH 9
/*

    The amount of memory (bytes) required to be allocated for the Name field.
    Equal to the longest name in Data_Names, "Assefa Ayalew Yoseph", plus the null terminator
*/
#define DATA_NAME_MAX_LENGTH 21

/* Constant, all user IDs. */
extern char *Data_IDs[];

/** Constant, all user's names. */
extern char *Data_Names[];

#endif
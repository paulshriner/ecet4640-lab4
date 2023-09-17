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
char *Data_IDs[DATA_NUM_RECORDS] = {
    "chen",
    "bea1389",
    "bol4559",
    "cal6258",
    "kre5277",
    "lon1150",
    "mas9309",
    "mes08346",
    "mil7233",
    "nef9476",
    "Nov-88",
    "pan9725",
    "rac3146",
    "rub4133",
    "shr5683",
    "vay3083",
    "yos2327"};

/** Constant, all user's names. */
char *Data_Names[DATA_NUM_RECORDS] = {
    "Weifeng Chen",
    "Christian Beatty",
    "Emily Bolles",
    "Cameron Calhoun",
    "Ty Kress",
    "Cody Long",
    "Caleb Massey",
    "Christian Messmer",
    "Karl Miller",
    "Jeremiah Neff",
    "Kaitlyn Novacek",
    "Joshua Panaro",
    "Caleb Rachocki",
    "Caleb Ruby",
    "Paul Shriner",
    "Alan Vayansky",
    "Assefa Ayalew Yoseph"};

#endif
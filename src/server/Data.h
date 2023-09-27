#ifndef Data_h
#define Data_h
/**
 * \file Data.h
 * @brief Declarations of types and macros.
   @details

   - DATA_NUM_RECORDS number of students to have records for
   - DATA_ID_MAX_LENGTH maximum length of Data_IDs can have
   - DATA_NAME_MAX_LENGTH maximum length among Data_Names
   - DATA_SIZE total size of a sutdent record
 */
#include <time.h>
#include <sys/types.h>

/**
    The total count of records.
*/
#define DATA_NUM_RECORDS 17
/**
    The amount of memory (bytes) required to be allocated for the ID field.
    Equal to the longest name in Data_IDs, "mes08346", plus the null terminator
*/
#define DATA_ID_MAX_LENGTH 9
/**
    The amount of memory (bytes) required to be allocated for the Name field.
    Equal to the longest name in Data_Names, "Assefa Ayalew Yoseph", plus the null terminator
*/
#define DATA_NAME_MAX_LENGTH 21

/* Constant, all user IDs. */
extern char *Data_IDs[];

/** Constant, all user's names. */
extern char *Data_Names[];

/**
    The size of one student record; the result of sizeof(Student).
*/
#define DATA_SIZE 56

/**
    @brief The student data type.
*/
typedef struct
{
    /// @brief The unique user ID.
    char userID[DATA_ID_MAX_LENGTH];
    /// @brief The user's full name.
    char fullName[DATA_NAME_MAX_LENGTH];
    /// @brief The user's age (randomized).
    short age;
    /// @brief The user's gpa (randomized).
    float gpa;
    /// @brief Whether the user is currently logged in (1) or not (0).
    short active;
    /// @brief The last time the user logged in.
    time_t lastLogin;
    /// @brief The cumulative time the user has been logged in since the server process started.
    int loginDuration;
} Student;

#endif
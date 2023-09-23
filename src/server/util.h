#ifndef util_h
#define util_h
/**
 * Contains utility functions that are not coupled to any other data or structures in the program.
 */

/**
    Returns an integer between min and max.
    @param min The minimum, inclusive.
    @param max The maximum, inclusive.
    @returns A random integer between min and max.
*/
int RandomInteger(int min, int max);

/**
    Returns a float between min and max.
    @param min The minimum, inclusive.
    @param max The maximum, inclusive.
    @returns A random integer between min and max.
*/
float RandomFloat(float min, float max);

/**
    Returns 1, percentage_chance of the time.
    @param percentage_chance The chance to return 1.
    @note If percentage_chance > 1, this will always return true.
    @returns 1 or 0
*/
short RandomFlag(float percentage_chance);

#endif
#include "util.h"

#include <stdlib.h>

int RandomInteger(int min, int max)
{
    int r_add = rand() % (max - min + 1);
    return r_add + min;
}

float RandomFloat(float min, float max)
{
    float dif = max - min;
    int rand_int = rand() % (int)(dif * 10000);
    return min + (float)rand_int / 10000.0;
}

short RandomFlag(float percentage_chance)
{
    float random_value = (float)rand() / RAND_MAX;
    if (random_value < percentage_chance)
    {
        return 1;
    }
    return 0;
}
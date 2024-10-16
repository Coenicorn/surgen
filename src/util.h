#ifndef UTIL_H
#define UTIL_H

#include "stdlib.h"

inline static float frand(float min, float max) 
{
    return (max - min) * ((float)rand() / (float)RAND_MAX) + min;
}

typedef struct AABB {
    float p1x, p1y;
    float p2x, p2y;
} AABB;

inline static int AABB_overlap(AABB a, AABB b)
{
    return (
        a.p1x < b.p2x &&
        a.p2x > b.p1x &&
        a.p1y < b.p2y &&
        a.p2y > b.p1y
    );
}

#endif // UTIL_H

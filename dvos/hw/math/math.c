
#include "../include/libs-hardware.h"

// MATH_PI = 3.141592653589793 * 256
#define MATH_PI         804


Int16 GetDegreeFromRadian(IntQ15 radian)
{
    Int32 tmp = radian * 180 * 32768;
    
    tmp = tmp / (MATH_PI * 256);
    
    return tmp;
}

IntQ15 GetRadianFromDegree(Int16 degree)
{
    Int32 tmp = degree * 32768 * MATH_PI;
    
    tmp = tmp / (180*256);
    
    return tmp;
}

RadianQ15 getRadianQ15FromDegree(Int16 degree)
{
    Int32 tmp = degree * 32768;
    return tmp / 360;
}

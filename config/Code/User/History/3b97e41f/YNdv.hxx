#pragma once
#include <cmath>

#define _USE_MATH_DEFINES
#ifdef _USE_MATH_DEFINES
    double pi = M_PI;

    #define DEG2RAD pi/180
    #define RAD2DEG 180/pi
#else
#endif
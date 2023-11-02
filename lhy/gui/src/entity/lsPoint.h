#ifndef LS_POINT_H
#define LS_POINT_H

#define _CRT_SECURE_NO_WARNINGS

typedef double lsReal;

#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define MAX(a, b) ((a) < (b)) ? (b) : (a)

typedef struct
{
    lsReal x;
    lsReal y;
    lsReal z;
} lsPoint;

#endif // LS_POINT_H

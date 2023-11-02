#ifndef LS_CIRCLE_H
#define LS_CIRCLE_H

#include "lsPoint.h"
#include "lsBoundbox.h"

typedef struct
{
    lsPoint c;
    lsReal r;
} lsCircle;

lsBoundbox ls_circle_get_boundbox(lsCircle *circle);

lsCircle ls_circle_scale(const lsCircle *circle, lsReal scale);

lsCircle ls_circle_translate(const lsCircle *circle, const lsPoint *vector);

#endif // LS_CIRCLE_H

#ifndef LS_ARC_H
#define LS_ARC_H

#include "lsPoint.h"
#include "lsBoundbox.h"

typedef struct
{
    lsPoint lup;
    lsPoint rlow;
    lsReal stangle;
    lsReal endangle;
}lsArc;

lsBoundbox ls_arc_get_boundbox(lsArc* arc);

lsArc ls_arc_scale(const lsArc* arc, lsReal scale);

lsArc ls_arc_translate(const lsArc* arc, const lsPoint* vector);





#endif

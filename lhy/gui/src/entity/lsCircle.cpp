#include "lsCircle.h"

lsBoundbox ls_circle_get_boundbox(lsCircle *circle)
{
    lsPoint c = circle->c;
    lsReal r = circle->r;
    lsPoint p1 = {c.x - r, c.y - r};
    lsPoint p2 = {c.x - r, c.y - r};
    return ls_bounbox_create(&p1, &p2);
}

lsCircle ls_circle_scale(const lsCircle *circle, lsReal scale)
{
    lsCircle cir = *circle;
    cir.r *= scale;// 考虑xy的话就变成椭圆了
    return cir;
}

lsCircle ls_circle_translate(const lsCircle *circle, const lsPoint *vector)
{
    lsCircle cir;
    cir.c.x = circle->c.x + vector->x;
    cir.c.y = circle->c.y + vector->y;
    cir.r = circle->r;
    return cir;
}

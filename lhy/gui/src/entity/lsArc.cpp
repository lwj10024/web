#include "lsArc.h"

lsBoundbox ls_arc_get_boundbox(lsArc* arc)
{
	return ls_bounbox_create(&arc->lup, &arc->rlow);
}

lsArc ls_arc_scale(const lsArc* arc, lsReal scale) 
{
	lsArc ar = *arc;
	ar.stangle *= scale;
	ar.endangle *= scale;
	return ar; 
}

lsArc ls_arc_translate(const lsArc* arc, const lsPoint* vector)
{
	lsArc ar;
	ar.lup.x = arc->lup.x + vector->x;
	ar.lup.y = arc->lup.y + vector->y;
	ar.rlow.x = arc->rlow.x + vector->x;
	ar.rlow.y = arc->rlow.y + vector->y;
	ar.stangle = arc->stangle;
	ar.endangle = arc->endangle;
	return ar;
}

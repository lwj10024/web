#include "lsEntity.h"

/**
 * @brief Convert lsPoint to lsEntity
 * 
 * @param point pointer to point
 * @return lsEntity 
 */
lsEntity ls_entity_convert_point(lsPoint *point)
{
    lsEntity entity;
    entity.type = kPoint;
    entity.data.point = *point;
    return entity;
}

/**
 * @brief Convert lsLine to lsEntity
 * 
 * @param line pointer to line
 * @return lsEntity 
 */
lsEntity ls_entity_convert_line(lsLine *line)
{
    lsEntity entity;
    entity.type = kLine;
    entity.data.line = *line;
    return entity;
}

/**
 * @brief Convert lsCircle to lsEntity
 * 
 * @param circle pointer to circle
 * @return lsEntity 
 */
lsEntity ls_entity_convert_circle(lsCircle *circle)
{
    lsEntity entity;
    entity.type = kCircle;
    entity.data.circle = *circle;
    return entity;
}

/**
 * @brief Convert lsArc eto lsEntity
 *
 * @param arc pointer to arc
 * @return lsEntity
 */
lsEntity ls_entity_convert_arc(lsArc* arc)
{
    lsEntity entity;
    entity.type = kArc;
    entity.data.arc = *arc;
    return entity;
}

lsEntity ls_entity_make_arc(lsReal lupx, lsReal lupy, lsReal rlowx, lsReal rlowy,lsReal stangle, lsReal endangle)
{
    lsEntity entity;

    lsPoint lup;
    lup.x = lupx;
    lup.y = lupy;


    lsPoint rlow;
    rlow.x = rlowx;
    rlow.y = rlowy;

    lsArc ar;
    ar.lup = lup;
    ar.rlow = rlow;
    ar.stangle = stangle;
    ar.endangle = endangle;

    entity.type = kArc;
    entity.data.arc = ar;

    return entity;
}


/**
 * @brief Get the boundbox of the entity
 * 
 * @param entity 
 * @return lsBoundbox 
 */
lsBoundbox ls_entity_get_boundbox(lsEntity *entity)
{
    lsBoundbox box;

    switch (entity->type)
    {
    case kLine:
        box = ls_line_get_boundbox(&entity->data.line);
        break;

    case kCircle:
        box = ls_circle_get_boundbox(&entity->data.circle);
        break;

    case kArc:
        box = ls_arc_get_boundbox(&entity->data.arc);
        break;

    default:
        break;
    }

    return box;
}

lsEntity ls_entity_scale(const lsEntity *entity, lsReal scalex, lsReal scaley)
{
    lsEntity ent;

    switch (entity->type)
    {
    case kLine:
        ent.data.line = ls_line_scale(&entity->data.line, scalex, scaley);
        ent = ls_entity_convert_line(&ent.data.line);
        break;

    case kCircle:
        ent.data.circle = ls_circle_scale(&entity->data.circle, scalex);
        ent = ls_entity_convert_circle(&ent.data.circle);
        break;


    case kArc:
        ent.data.arc = ls_arc_scale(&entity->data.arc, scalex);
        ent = ls_entity_convert_arc(&ent.data.arc);
        break;

    default:
        ent.type = kUnknown;
        break;
    }

    return ent;
}

lsEntity ls_entity_translate(const lsEntity *entity, const lsPoint *vector)
{
    lsEntity ent;

    switch (entity->type)
    {
    case kLine:
        ent.data.line = ls_line_translate(&entity->data.line, vector);
        ent = ls_entity_convert_line(&ent.data.line);
        break;
        
    case kCircle:
        ent.data.circle = ls_circle_translate(&entity->data.circle, vector);
        ent = ls_entity_convert_circle(&ent.data.circle);
        break;

    case kArc:
        ent.data.arc = ls_arc_translate(&entity->data.arc, vector);
        ent = ls_entity_convert_arc(&ent.data.arc);
        break;

    default:
        ent.type = kUnknown;
        break;
    }

    return ent;
}

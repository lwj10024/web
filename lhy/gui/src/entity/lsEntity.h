#ifndef LS_ENTITY_H
#define LS_ENTITY_H

#define _CRT_SECURE_NO_WARNINGS

#include "lsPoint.h"
#include "lsLine.h"
#include "lsCircle.h"
#include "lsArc.h"
#include "lsBoundbox.h"

typedef enum
{
    kUnknown = 0,
    kPoint,
    kLine,
    kArc,
    kCircle,
    kXLine
} EntityType;

typedef union
{
    lsPoint point;
    lsLine line;
    lsCircle circle;
    lsArc arc;
} EntityData;

typedef struct
{
    EntityType type;
    EntityData data;
} lsEntity;

/**
 * @brief Convert lsPoint to lsEntity
 * 
 * @param point pointer to point
 * @return lsEntity 
 */
lsEntity ls_entity_convert_point(lsPoint *point);

/**
 * @brief Convert lsLine to lsEntity
 * 
 * @param line pointer to line
 * @return lsEntity 
 */
lsEntity ls_entity_convert_line(lsLine *line);

/**
 * @brief Convert lsCircle to lsEntity
 * 
 * @param circle pointer to circle
 * @return lsEntity 
 */
lsEntity ls_entity_convert_circle(lsCircle *circle);

/**
 * @brief Convert lsArc to lsEntity
 *
 * @param arc pointer to arc
 * @return lsEntity
 */
lsEntity ls_entity_convert_arc(lsArc* arc);


lsEntity ls_entity_make_arc(lsReal lupx, lsReal lupy, lsReal rlowx, lsReal rlowy, lsReal stangle, lsReal endangle);


/**
 * @brief Get the boundbox of the entity
 * 
 * @param entity 
 * @return lsBoundbox 
 */
lsBoundbox ls_entity_get_boundbox(lsEntity *entity);

lsEntity ls_entity_scale(const lsEntity *entity, lsReal scalex, lsReal scaley);

lsEntity ls_entity_translate(const lsEntity *entity, const lsPoint *vector);

#endif // LS_ENTITY_H

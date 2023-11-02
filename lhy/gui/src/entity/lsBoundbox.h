#ifndef LS_BOUNDBOX_H
#define LS_BOUNDBOX_H

#include "lsPoint.h"

typedef struct _lsBoundbox
{
    _lsBoundbox() : left(0.0), top(0.0), right(0.0), bottom(0.0) {} // C++特性，初始化列表，在创建结构体变量时能够将成员变量初始化为0

    lsReal left;
    lsReal top;
    lsReal right;
    lsReal bottom;
} lsBoundbox;

/**
 * @brief Create box from two point
 * 
 * @param p1 
 * @param p2 
 * @return lsBoundbox 
 */
lsBoundbox ls_bounbox_create(lsPoint *p1, lsPoint *p2);

/**
 * @brief Get the box min point(left, bottom)
 * 
 * @param box 
 * @return lsPoint 
 */
lsPoint ls_boundbox_min(lsBoundbox *box);

/**
 * @brief Get the box max point(right, top)
 * 
 * @param box 
 * @return lsPoint 
 */
lsPoint ls_boundbox_max(lsBoundbox *box);

/**
 * @brief Combine two box to a box
 * 
 * @param box1 
 * @param box2 
 * @return lsBoundbox 
 */
lsBoundbox ls_boundbox_combine(lsBoundbox *box1, lsBoundbox *box2);

lsReal ls_boundbox_width(lsBoundbox *box);

lsReal ls_boundbox_height(lsBoundbox *box);

lsPoint ls_boundbox_center(lsBoundbox *box);

#endif // LS_BOUNDBOX_H

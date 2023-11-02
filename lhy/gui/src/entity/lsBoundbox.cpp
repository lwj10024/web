#include "lsBoundbox.h"

/**
 * @brief Create box from two point
 * 
 * @param p1 
 * @param p2 
 * @return lsBoundbox 
 */
lsBoundbox ls_bounbox_create(lsPoint *p1, lsPoint *p2)
{
    lsBoundbox box;

    box.left = MIN(p1->x, p2->x);
    box.right = MAX(p1->x, p2->x);
    box.bottom = MIN(p1->y, p2->y);
    box.top = MAX(p1->y, p2->y);
    return box;
}

/**
 * @brief Get the box min point(left, bottom)
 * 
 * @param box 
 * @return lsPoint 
 */
lsPoint ls_boundbox_min(lsBoundbox *box)
{
    lsPoint pt;
    pt.x = box->left;
    pt.y = box->bottom;
    return pt;
}

/**
 * @brief Get the box max point(right, top)
 * 
 * @param box 
 * @return lsPoint 
 */
lsPoint ls_boundbox_max(lsBoundbox *box)
{
    lsPoint pt;
    pt.x = box->right;
    pt.y = box->top;
    return pt;
}

/**
 * @brief Combine two box to a box
 * 
 * @param box1 
 * @param box2 
 * @return lsBoundbox 
 */
lsBoundbox ls_boundbox_combine(lsBoundbox *box1, lsBoundbox *box2)
{
    lsBoundbox box;
    box.left = MIN(box1->left, box2->left);
    box.right = MAX(box1->right, box2->right);
    box.bottom = MIN(box1->bottom, box2->bottom);
    box.top = MAX(box1->top, box2->top);
    return box;
}

lsReal ls_boundbox_width(lsBoundbox *box)
{
    return box->right - box->left;
}

lsReal ls_boundbox_height(lsBoundbox *box)
{
    return box->top - box->bottom;
}

lsPoint ls_boundbox_center(lsBoundbox *box)
{
    lsPoint center;
    center.x = box->left + ls_boundbox_width(box) / 2;
    center.y = box->bottom + ls_boundbox_height(box) / 2;
    return center;
}

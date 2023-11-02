#include <conio.h>

#include "lsCanvas.h"
#include "lsBoundbox.h"

/**
 * @brief 初始化画布。启动窗口。
 * 
 * @param canvas 画布指针
 */
void ls_canvas_init(lsCanvas *canvas, int w, int h)
{
    if (!canvas)
        return;

    canvas->w = w;
    canvas->h = h;

    initgraph(canvas->w, canvas->h);
}

/**
 * @brief 从实体数组往画布加载实体
 * 
 * @param canvas 画布指针
 * @param entitys 实体数组指针
 */
void ls_canvas_load_entity(lsCanvas *canvas, std::vector<lsEntity> *entitys)
{
    for (size_t i = 0; i < entitys->size(); ++i)
        canvas->entitys.push_back((*entitys)[i]);
    canvas->bDirty = true;
}

/**
 * @brief 画布添加实体
 * 
 * @param canvas 
 * @param entity 
 */
void ls_canvas_add_entity(lsCanvas *canvas, lsEntity entity)
{
    if (!canvas)
        return;

    canvas->entitys.push_back(entity);
    canvas->bDirty = true;// 数据脏了，需要重新绘制，会全部重绘
}

/**
 * @brief 画布双缓冲绘图刷新。并不是重绘。
 * 
 * @param canvas 
 */
void ls_canvas_flush(lsCanvas *canvas)
{
    FlushBatchDraw();
    Sleep(100);
}

/**
 * @brief 画布重绘
 * 
 * @param canvas 
 */
void ls_canvas_redraw(lsCanvas *canvas)
{
    if (!canvas)
        return;
    if (!canvas->bDirty)
        return;// 不脏就不绘制了

    // 先求出全部实体的边界盒
    lsBoundbox box;
    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsBoundbox subbox = ls_entity_get_boundbox(&canvas->entitys[i]);
        box = ls_boundbox_combine(&box, &subbox);
    }

    // 图形中心平移到和窗口中心重合

    lsPoint windowCenter = {canvas->w / 2, canvas->h / 2};
    lsPoint boxCenter = ls_boundbox_center(&box);
    lsPoint translate;
    translate.x = windowCenter.x - boxCenter.x;
    translate.y = windowCenter.y - boxCenter.y;

    lsReal boxw = ls_boundbox_width(&box), boxh = ls_boundbox_height(&box);
    lsReal scalex = boxw / canvas->w, scaley = boxh / canvas->h;
    lsReal scale = MAX(scalex, scaley);
    scale = 1 / scale;

    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsEntity entity = canvas->entitys[i];
        entity = ls_entity_translate(&entity, &translate);// 平移使得图形中心和窗口中心重合
        entity = ls_entity_scale(&entity, scale, scale);// 缩放使得整个图形在窗口范围可见

        // 窗口坐标原点在左上角，X轴正方向是向右，Y轴正方向是向下，而图元坐标系原点在左下角，X轴正方向是向右，Y轴正方向是向上，所以Y轴需要进行变换
        switch (entity.type)
        {
        case kLine:
            lsLine l = entity.data.line;
            l.s.y = canvas->h - l.s.y;
            l.e.y = canvas->h - l.e.y;
            line(l.s.x, l.s.y, l.e.x, l.e.y);
            break;

        case kCircle:
            lsCircle cir = entity.data.circle;
            cir.c.y = canvas->h - cir.c.y;
            circle((int)cir.c.x, (int)cir.c.y, (int)cir.r);
            break;
        
        case kArc:
            lsArc ar = entity.data.arc;
            ar.lup.y = canvas->h - ar.lup.y;
            ar.rlow.y = canvas->h - ar.rlow.y;
            arc((int)ar.lup.x, (int)ar.lup.y, (int)ar.rlow.x,(int)ar.rlow.y,(int)ar.stangle,(int)ar.endangle);
            break;

        default:
            break;
        }
    }

    canvas->bDirty = false;
}

/**
 * @brief 画布轮询。在这里响应按键。
 * 
 * @param canvas 
 */
void ls_canvas_polling(lsCanvas *canvas)
{
    if (!canvas)
        return;

    BeginBatchDraw();

    while (1)
    {
        ls_canvas_flush(canvas);
        ls_canvas_redraw(canvas);

        if (_kbhit())
            break;
    }

    EndBatchDraw();
}

/**
 * @brief 销毁画布
 * 
 * @param canvas 
 */
void ls_canvas_destroy(lsCanvas *canvas)
{
    closegraph();

    if (NULL == canvas)
        return;
}

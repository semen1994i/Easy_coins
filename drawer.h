#ifndef DRAWER_H
#define DRAWER_H

#include "maps.h"
#include <QGLWidget>
#include <vector>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>

struct drawer
{
    drawer();

    void draw(const level&, QGLWidget &);

private:

    void _draw_grid(const level&, QGLWidget &);

    void _draw_objects(const level&, QGLWidget &);

    void _draw_statistic(const level&, QGLWidget &);


private:

    bool mTextureIsLoad{false};
};

#endif // DRAWER_H

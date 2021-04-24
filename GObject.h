#ifndef GOBJECT_H
#define GOBJECT_H

#include <QOpenGLWindow>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QtOpenGL>

class GObject {
    // A vertex array allows you to draw a an object after defining it once.
    // For examples on how to use the VAO, see the example classes
    // Update: this is no longer the route I am taking, as I am having issues getting this working. I will try to get this working later
protected:
    // QOpenGLVertexArrayObject VAO;

public:
    GObject ();
    GObject (float _x, float _y, float _z);
    ~GObject ();

    // will draw the object. Would be much more lightweight if I can get the VAO working, so I will be trying to get that to work later
    // For now follow the examples on
    virtual void draw(float cam_x, float cam_y, float cam_z, float cam_x_r, float cam_y_r, float cam_z_r) = 0;

    // If you want to have any game logic, this is where it should go
    virtual void update() = 0;

    inline static QOpenGLContext *context; // these two are needed to draw properly
    inline static QOpenGLWindow *window;
    float x, y, z;
};

#endif // GOBJECT_H
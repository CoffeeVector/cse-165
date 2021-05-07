#ifndef GROUND_H
#define GROUND_H

#include <QOpenGLWindow>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QtOpenGL>

#include "Tetris.h"

class Ground {
    float x, y, z; // central position
    float w, l;
public:
    Ground(Tetris *t) : x(0), y(0), z(0), w(t->w), l(t->l) {}
    ~Ground () {}

    void draw(float bl_sz)  {
        // Green background
        float border = 2.0f; // how much green space to have. Set to a large number for the entire background to be green
        glPolygonMode(GL_BACK, GL_FILL); // Change to GL_FRONT_AND_BACK if you want the other side to be filled as well
        glBegin(GL_POLYGON);
            glColor3f(0.1f, 0.9f, 0.2f); // the main green background (grass I guess)
            glVertex3f(-border,             -border,             -0.02f);
            glVertex3f(-border,              border + bl_sz * l, -0.02f);
            glVertex3f( border + bl_sz * w,  border + bl_sz * l, -0.02f);
            glVertex3f( border + bl_sz * w, -border,             -0.02f);
        glEnd();

        // grey play area
        glPolygonMode(GL_BACK, GL_FILL); // Change to GL_FRONT_AND_BACK if you want the other side to be filled as well
        glBegin(GL_POLYGON);
            glColor3f(0.8f, 0.8f, 0.8f); // the grey play area
            glVertex3f(0.0f,      0.0f,      -0.01f);
            glVertex3f(0.0f,      bl_sz * l, -0.01f);
            glVertex3f(bl_sz * w, bl_sz * l, -0.01f);
            glVertex3f(bl_sz * w, 0.0f,      -0.01f);
        glEnd();

        // If you want to turn off the grid, comment this out
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(1);
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < l; j++) {
                glBegin(GL_POLYGON);
                    glColor3f(0.2f, 0.2f, 0.2f); // a grid to make the spaces more obvious
                    glVertex3f(0.0f  + i * bl_sz, 0.0f  + j * bl_sz, 0.0f);
                    glVertex3f(0.0f  + i * bl_sz, bl_sz + j * bl_sz, 0.0f);
                    glVertex3f(bl_sz + i * bl_sz, bl_sz + j * bl_sz, 0.0f);
                    glVertex3f(bl_sz + i * bl_sz, 0.0f  + j * bl_sz, 0.0f);
                glEnd();
            }
        }
    }
};
#endif

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

    void draw (float cam_x, float cam_y, float cam_z, float cam_x_r, float cam_y_r, float cam_z_r, float bl_sz) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Positions the camera // Note: when the modelview matrix is broken into the model and view matrix, this isn't necessary
        glTranslatef(x,y,z);
        glTranslatef(cam_x,cam_y,cam_z);
        glRotatef(cam_x_r, 1.0f,0.0f,0.0f);
        glRotatef(cam_y_r, 0.0f,1.0f,0.0f);
        glRotatef(cam_z_r, 0.0f,0.0f,1.0f);

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

        glFlush();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
};








#endif // GROUND_H

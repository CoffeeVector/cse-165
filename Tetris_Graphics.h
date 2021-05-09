#ifndef TETRIS_GRAPHICS_H
#define TETRIS_GRAPHICS_H

#include <QOpenGLWindow>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QtOpenGL>

#include "Tetris.h"

class TetrisGraphics {
    Tetris* t;
public:
    TetrisGraphics(Tetris *t) {
        this->t = t;
    }

    void draw() {
        int x, y, z;
        float r, g, b;
        float distance = 1;
        float block_width = 0.9;
        //float color_width = 0.9;
        for (int i = 0; i < t->w*t->l*t->h; i++) {
            t->ind2sub(i, x, y, z);
            if (t->state[x][y][z] != NULL) {
                r = ((float) t->state[x][y][z]->r) / 255;
                g = ((float) t->state[x][y][z]->g) / 255;
                b = ((float) t->state[x][y][z]->b) / 255;
                int cube_coords[4*6][3] = {
                    //bottom
                    {0, 0, 0},
                    {1, 0, 0},
                    {1, 1, 0},
                    {0, 1, 0},
                    //top
                    {0, 0, 1},
                    {1, 0, 1},
                    {1, 1, 1},
                    {0, 1, 1},
                    //front
                    {0, 0, 0},
                    {0, 1, 0},
                    {0, 1, 1},
                    {0, 0, 1},
                    //back
                    {1, 0, 0},
                    {1, 1, 0},
                    {1, 1, 1},
                    {1, 0, 1},
                    //left
                    {0, 0, 0},
                    {0, 0, 1},
                    {1, 0, 1},
                    {1, 0, 0},
                    //right
                    {0, 1, 0},
                    {0, 1, 1},
                    {1, 1, 1},
                    {1, 1, 0},
                };

                int mode[] = {GL_FILL, GL_LINE};
                glLineWidth(5);
                for (int i = 0; i < 2; i++) { // draw twice, once with borders, and another wth fill
                    glPolygonMode(GL_FRONT_AND_BACK, mode[i]);
                    glBegin(GL_QUADS); // bottom
                        if (i == 0) {
                            glColor3f(r, g, b);
                        } else {
                            glColor3f(0, 0, 0);
                        }
                        for (int corner = 0; corner < 24; corner++) {
                            glVertex3f(
                                distance*x + block_width*cube_coords[corner][0],
                                distance*y + block_width*cube_coords[corner][1],
                                distance*z + block_width*cube_coords[corner][2]
                            );
                        }
                    glEnd();
                }
            }
        }
    }
};
#endif

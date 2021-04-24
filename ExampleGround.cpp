#include "ExampleGround.h"

ExampleGround::ExampleGround() : GObject() {
    /*context->makeCurrent(window);
    VAO.bind();

    // for now we're going to assume that down is y
    // this can be changed if we want to make the camera more in depth

    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f); //red
        glVertex3f(100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, 100.0f);
     glEnd();

     VAO.release(); */
}

ExampleGround::ExampleGround(float _x, float _y, float _z) : GObject(_x,_y,_z) {
    /*context->makeCurrent(window);
    VAO.bind();

    // for now we're going to assume that down is y
    // this can be changed if we want to make the camera more in depth

    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f); //red
        glVertex3f(100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, 100.0f);
     glEnd();

     VAO.release();*/
}


ExampleGround::~ExampleGround() {}

void ExampleGround::draw (float cam_x, float cam_y, float cam_z, float cam_x_r, float cam_y_r, float cam_z_r) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(cam_x_r, 1.0f,0.0f,0.0f);
    glRotatef(cam_y_r, 0.0f,1.0f,0.0f);
    glRotatef(cam_z_r, 0.0f,0.0f,1.0f);
    glTranslatef(x,y,z);
    glTranslatef(cam_x,cam_y,cam_z);



    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f); //red
        glVertex3f(10.0f, 0.0f, 10.0f);
        glVertex3f(10.0f, 0.0f, -10.0f);
        glVertex3f(-10.0f, 0.0f, -10.0f);
        glVertex3f(-10.0f, 0.0f, 10.0f);
     glEnd();
     glBegin(GL_POLYGON);
         glColor3f(0.6f, 0.6f, 0.6f); //grey
         glVertex3f(1.0f, 2.0f, -1.0f);
         glVertex3f(1.0f, 0.0f, -1.0f);
         glVertex3f(-1.0f, 0.0f, -1.0f);
         glVertex3f(-1.0f, 2.0f, -1.0f);
      glEnd();






    glFlush();
}


void ExampleGround::update () { // in this case, the update function is unnecessary



}


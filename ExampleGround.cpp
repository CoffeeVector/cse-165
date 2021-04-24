#include "ExampleGround.h"

ExampleGround::ExampleGround() : GObject() {
    /*context->makeCurrent(window); // This code does not work right now, and is designed for a more efficent draw approach.
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
    /*context->makeCurrent(window); // This code does not work right now, and is designed for a more efficent draw approach.
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

// This is the most basic object possible: it is nothing but a square.
void ExampleGround::draw () {
    // This should not be changed, as this positions the object
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Positions the camera
    glRotatef(*cam_x_r, 1.0f,0.0f,0.0f);
    glRotatef(*cam_y_r, 0.0f,1.0f,0.0f);
    glRotatef(*cam_z_r, 0.0f,0.0f,1.0f);
    glTranslatef(x,y,z);
    glTranslatef(*cam_x,*cam_y,*cam_z);

    // Your code should go here.
    glBegin(GL_POLYGON);
        glColor3f(0.6f, 0.6f, 0.6f); // grey // I'll work on getting textures working if you want me to.
        glVertex3f(100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, 100.0f);
    glEnd();

    // This needs to be at the end of the draw function: it basically pushes the changes to the screen
    glFlush();
}


void ExampleGround::update () { // in this case, the update function is unnecessary, as the ground should not do anything on its own.



}


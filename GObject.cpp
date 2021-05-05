#include "GObject.h"

GObject::GObject() : x(0), y(0), z(0) {
    /*// This will setup the VAO. To actually create something that can be drawn, you need to bind it. See the example classed for how to do this
    context->makeCurrent(window);

    VAO.create();

    if(VAO.isCreated() != true) { // I don't know if this can happen, but its probably a good idea to do this anyway
        throw("Cannot create GObject");
    }*/
}


GObject::GObject(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {
    /*// This will setup the VAO. To actually create something that can be drawn, you need to bind it. See the example classed for how to do this
    context->makeCurrent(window);
    if (context -> isValid() != true) {
        throw("Context not current");
    }
    VAO.create();

    if(VAO.isCreated() != true) { // I don't know if this can happen, but its probably a good idea to do this anyway
        throw("Cannot create GObject");
    } */
}


GObject::~GObject() {
//    VAO.release();
}

/// So what I was initially trying to do here was to draw the object with a VertexArrayObject
/// Because of how VAOs work, you would not need to specify which points to draw on here, as you would simply draw from an existing VAO
/// This did not work
/// I was having issues getting the VAO to recognize the context, and have decided for now to go with the inefficient method
/// I will be working on trying to fix this
/// Don't worry about objects that you create becoming incompatible, as fixing them should just involve moving the polygon definitions to the constructor
// I'm not currently sure if we can use the model and view matrices separately with QT, so for now the camera has to be passed into the draw function
// TODO -> Hunter: fix / refine this
// Also TODO -> Hunter: Get the VAO working, that would make this so much simpler
/*void GObject::draw (float cam_x, float cam_y, float cam_z, float cam_x_r, float cam_y_r, float cam_z_r) {
    context->makeCurrent(window);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //VAO.bind();

    glTranslatef(x,y,z);
    glRotatef(cam_x_r, 1.0f,0.0f,0.0f);
    glRotatef(cam_y_r, 0.0f,1.0f,0.0f);
    glRotatef(cam_z_r, 0.0f,0.0f,1.0f);
    glTranslatef(cam_x,cam_y,cam_z);


    glFlush();

    VAO.release();
}*/


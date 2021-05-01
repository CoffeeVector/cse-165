#include "ExampleBrick.h"

// The constructors set the variable that will be checked frequently
ExampleBrick::ExampleBrick (ExampleGround *e) : GObject() {
    ground = e;
}

ExampleBrick::ExampleBrick (float _x, float _y, float _z, ExampleGround *e) : GObject(_x, _y, _z) {
    ground = e;
}

// Like the ground class, this class also doesn't need a specific deconstructor
ExampleBrick::~ExampleBrick() {}

// The draw function works in the same way as ExampleGround's draw function. the middle-end will be different because that is currently how we draw things, but overall it will effectively be the same
void ExampleBrick::draw() {
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
    glBegin(GL_POLYGON); // Bottom
        glColor3f(0.9f, 0.2f, 0.2f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON); // Top
        glColor3f(0.9f, 0.2f, 0.2f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON); // Front
        glColor3f(0.9f, 0.2f, 0.2f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON); // Back
        glColor3f(0.9f, 0.2f, 0.2f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    glBegin(GL_POLYGON); // Left
        glColor3f(0.9f, 0.2f, 0.2f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();

    glBegin(GL_POLYGON); // Right
        glColor3f(0.9f, 0.2f, 0.2f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    // This needs to be at the end of the draw function: it basically pushes the changes to the screen
    glFlush();

}

void ExampleBrick::update () {
    if (!grounded) {
        y -= 0.05;
        if (y - 0.5 <= ground->y) {
            grounded = true;
        }
    }
}

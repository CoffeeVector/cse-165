#ifndef EXAMPLEGROUND_H
#define EXAMPLEGROUND_H

#include "GObject.h"

class ExampleGround : public GObject {
public:
    ExampleGround();
    ExampleGround(float _x, float _y, float _z);
    ~ExampleGround();

    void draw(float cam_x, float cam_y, float cam_z, float cam_x_r, float cam_y_r, float cam_z_r);
    void update();
};

#endif // EXAMPLEGROUND_H
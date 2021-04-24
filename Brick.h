#ifndef BRICK_H
#define BRICK_H

#include "GObject.h"
#include "ExampleGround.h"

// The ground class does nothing. this class will create a block that falls until it hits the ground
class Brick : public GObject {
    Brick (ExampleGround e);
    Brick (float _x, float _y, float _z, ExampleGround e);
    ~Brick ();

    void draw ();
    void update ();
};



#endif // BRICK_H

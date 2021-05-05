#ifndef EXAMPLEBRICK_H
#define EXAMPLEBRICK_H

#include "GObject.h"
#include "ExampleGround.h"

// The ground class does nothing. this class will create a block that falls until it hits the ground
class ExampleBrick : public GObject {
    ExampleGround *ground;
    bool grounded = false; // if the object has hit the ground
public:
    ExampleBrick (ExampleGround *e);
    ExampleBrick (float _x, float _y, float _z, ExampleGround *e);
    ~ExampleBrick ();

    void draw ();
    void update ();
};

#endif // EXAMPLEBRICK_H

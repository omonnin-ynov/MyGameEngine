#pragma once
#include <box2d/box2d.h>

namespace MGE {

    class ICollidable
    {
    public:
        virtual void BeginCollision(b2Contact* contact) = 0;
        virtual void EndCollision(b2Contact* contact) = 0;
    };
}

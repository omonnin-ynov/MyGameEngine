#pragma once
#include <box2d/box2d.h>
#include "Collision.h"

namespace MGE {

    class ICollidable
    {
    public:
        virtual void BeginCollision(Collision collision) = 0;
        virtual void EndCollision(Collision collision) = 0;
    };
}

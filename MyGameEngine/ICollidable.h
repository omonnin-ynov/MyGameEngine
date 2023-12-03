#pragma once
#include "Collision.h"

namespace MGE {

    class ICollidable
    {
    public:
        virtual void BeginCollision(Collision collision) = 0;
        virtual void EndCollision(Collision collision) = 0;
    };
}

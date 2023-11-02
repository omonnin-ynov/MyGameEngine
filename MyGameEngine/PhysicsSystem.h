#pragma once
#include <box2d/box2d.h>
#include "CollisionListener.h"

namespace MGE {
    class PhysicsSystem
    {
    protected:
        b2World _world;
        CollisionListener _collisionListener;

    public:
        inline static const float WorldScale = 30.0f;

        PhysicsSystem(b2Vec2 gravity);

        void Update(float deltaTime);

        b2World* getWorld();
        void setGravity(b2Vec2 gravity);
    };
}

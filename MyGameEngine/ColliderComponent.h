#pragma once
#include "AComponent.h"
#include <box2d/box2d.h>

namespace MGE {
    class ColliderComponent :
        public AComponent
    {
    protected:
        b2FixtureDef _fixtureDef;
        b2Fixture* _fixture;

    public:
        ColliderComponent();

        virtual void createFixture(b2Body& body);
        virtual const b2Shape* getColliderShape() = 0;

        void setDensity(float density);
        void setFriction(float friction);
    };

}

#pragma once
#include "AComponent.h"
#include <box2d/box2d.h>

namespace MGE {
    class ColliderComponent:
        public AComponent
    {
    protected:
        b2FixtureDef _fixtureDef;
        b2Fixture* _fixture;

    public:
        ColliderComponent(std::string name);

        virtual const b2Shape* getColliderShape() = 0;

        void setDensity(float density) const;
        void setFriction(float friction) const;
        void createFixture(b2Body& body);
    };

}

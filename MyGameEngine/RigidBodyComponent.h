#pragma once
#include "AComponent.h"
#include <box2d/box2d.h>

namespace MGE {
    class RigidBodyComponent :
        public AComponent
    {
    protected:
        b2BodyDef _bodyDef;
        b2Body* _body;

    public:
        RigidBodyComponent(std::string name);
        b2Body* getBody();

        b2BodyType getBodyType();
        void setBodyType(b2BodyType bodyType);

        const b2Transform& getTransform();
        void setTransform(b2Vec2 position, float angle);

        const b2Vec2& getPosition();
        void setPosition(b2Vec2 position);

        float getAngle();

        float getAngularVelocity();
        void setAngularVelocity(float omega);

        void SetLinearVelocity(const b2Vec2 v);
        const b2Vec2 GetLinearVelocity();
    };
}

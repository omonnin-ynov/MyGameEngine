#pragma once
#include "AComponent.h"
#include <box2d/box2d.h>
#include "ICollidable.h"

namespace MGE {
    class RigidBodyComponent :
        public AComponent
    {
    protected:
        b2BodyDef _bodyDef;
        b2Body* _body;

    public:
        RigidBodyComponent(std::string name);
        ~RigidBodyComponent() override;

        void Awake() override;
        void Start() override;
        void Update(float deltaTime) override;
        void LateUpdate(float deltaTime) override;

        b2Body* getBody() const;
        b2BodyType getBodyType() const;
        void setBodyType(b2BodyType bodyType);

        const b2Transform& getTransform() const;
        void setTransform(b2Vec2 position, float angle);

        const b2Vec2& getPosition() const;
        void setPosition(b2Vec2 position);

        float getAngle() const;

        float getAngularVelocity() const;
        void setAngularVelocity(float omega);

        void SetLinearVelocity(const b2Vec2 v);
        const b2Vec2 GetLinearVelocity() const;
    };
}

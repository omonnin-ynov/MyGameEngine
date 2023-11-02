#pragma once
#include "ColliderComponent.h"

namespace MGE {
    class BoxCollider :
        public ColliderComponent
    {
    protected:
        b2PolygonShape _shape;
        float _x;
        float _y;

    public:
        BoxCollider(std::string name);
        void createFixture(b2Body& body);
        
        virtual void Awake() override;
        virtual void Start() override;
        virtual void Update(float deltaTime) override;
        virtual void LateUpdate(float deltaTime) override;

        const b2Shape* getColliderShape();
        void setHalfSize(float x, float y);
    };
}

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
        BoxCollider(std::string name, b2FixtureDef fixtureDef);
        
        virtual void Awake() override;
        virtual void Start() override;
        virtual void Update(float deltaTime) override;
        virtual void LateUpdate(float deltaTime) override;

        const b2Shape* getColliderShape() override;
        void setHalfSize(float x, float y);
    };
}

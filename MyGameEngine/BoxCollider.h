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

        void Awake() override;
        void Start() override;
        void Update(float deltaTime) override;
        void LateUpdate(float deltaTime) override;

        const b2Shape* getColliderShape() override;
        void setHalfSize(float x, float y);
        b2PolygonShape* shape();
        void set_shape(b2PolygonShape shape);
    };
}

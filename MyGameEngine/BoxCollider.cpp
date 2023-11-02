#include "BoxCollider.h"
#include "Application.h"

MGE::BoxCollider::BoxCollider(std::string name) : _shape()
{
    _x = 4.0f;
    _y = 4.0f;
    _shape.SetAsBox(_x, _y);
    _fixtureDef.shape = &_shape;
    _fixtureDef.density = 1.0f;
    _fixtureDef.friction = 0.3f;
}

void MGE::BoxCollider::createFixture(b2Body& body)
{
    _fixture = body.CreateFixture(&_fixtureDef);
}

void MGE::BoxCollider::Awake()
{
}

void MGE::BoxCollider::Start()
{
}

void MGE::BoxCollider::Update(float deltaTime)
{
}

void MGE::BoxCollider::LateUpdate(float deltaTime)
{
}

const b2Shape* MGE::BoxCollider::getColliderShape()
{
    return &_shape;
}

void MGE::BoxCollider::setHalfSize(float x, float y)
{
    _x = x;
    _y = y;
    _shape.SetAsBox(_x, _y);
}

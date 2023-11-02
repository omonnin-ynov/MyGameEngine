#include "RigidBodyComponent.h"
#include "Application.h"

MGE::RigidBodyComponent::RigidBodyComponent(std::string name) : _bodyDef()
{
    _body = Application::getInstance()->getWorld()->CreateBody(&_bodyDef);
}

b2Body* MGE::RigidBodyComponent::getBody()
{
    return _body;
}

b2BodyType MGE::RigidBodyComponent::getBodyType()
{
    return _body->GetType();
}

void MGE::RigidBodyComponent::setBodyType(b2BodyType bodyType)
{
    _body->SetType(bodyType);
}

const b2Transform& MGE::RigidBodyComponent::getTransform()
{
    return _body->GetTransform();
}

/// <summary>
/// Sets the body's tranform. +x is right and +y is down, angle is counter-clockwise in radians.
/// </summary>
/// <param name="position"></param>
/// <param name="angle"></param>
void MGE::RigidBodyComponent::setTransform(b2Vec2 position, float angle)
{
    _body->SetTransform(position, angle);
}

const b2Vec2& MGE::RigidBodyComponent::getPosition()
{
    return _body->GetTransform().p;
}

void MGE::RigidBodyComponent::setPosition(b2Vec2 position)
{
    _body->SetTransform(position, _body->GetAngle());
}

float MGE::RigidBodyComponent::getAngle()
{
    return _body->GetAngle();
}

float MGE::RigidBodyComponent::getAngularVelocity()
{
    return _body->GetAngularVelocity();
}

void MGE::RigidBodyComponent::setAngularVelocity(float omega)
{
    _body->SetAngularVelocity(omega);
}

void MGE::RigidBodyComponent::SetLinearVelocity(const b2Vec2 v)
{
    _body->SetLinearVelocity(v);
}

const b2Vec2 MGE::RigidBodyComponent::GetLinearVelocity()
{
     return _body->GetLinearVelocity();
}

#include "RigidBodyComponent.h"
#include "Application.h"

MGE::RigidBodyComponent::RigidBodyComponent(std::string name) : _bodyDef()
{
    _body = Application::getInstance()->getWorld()->CreateBody(&_bodyDef);
    (*Application::getInstance()->getb2BodyToComp())[_body] = this;
}

MGE::RigidBodyComponent::~RigidBodyComponent()
{
    Application::getInstance()->getb2BodyToComp()->erase(_body);
    Application::getInstance()->getWorld()->DestroyBody(_body);
}

void MGE::RigidBodyComponent::Awake()
{
}

void MGE::RigidBodyComponent::Start()
{
}

void MGE::RigidBodyComponent::Update(float deltaTime)
{
}

void MGE::RigidBodyComponent::LateUpdate(float deltaTime)
{
}

b2Body* MGE::RigidBodyComponent::getBody() const
{
    return _body;
}

b2BodyType MGE::RigidBodyComponent::getBodyType() const
{
    return _body->GetType();
}

void MGE::RigidBodyComponent::setBodyType(b2BodyType bodyType)
{
    _body->SetType(bodyType);
}

const b2Transform& MGE::RigidBodyComponent::getTransform() const
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

const b2Vec2& MGE::RigidBodyComponent::getPosition() const
{
    return _body->GetTransform().p;
}

void MGE::RigidBodyComponent::setPosition(b2Vec2 position)
{
    _body->SetTransform(position, _body->GetAngle());
}

float MGE::RigidBodyComponent::getAngle() const
{
    return _body->GetAngle();
}

float MGE::RigidBodyComponent::getAngularVelocity() const
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

const b2Vec2 MGE::RigidBodyComponent::GetLinearVelocity() const
{
     return _body->GetLinearVelocity();
}

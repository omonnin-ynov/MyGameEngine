#include "ColliderComponent.h"

#include "Application.h"

void Update() {

}

MGE::ColliderComponent::ColliderComponent(std::string name) : AComponent(name), _fixtureDef()
{
}


void MGE::ColliderComponent::createFixture(b2Body& body)
{
    _fixture = body.CreateFixture(&_fixtureDef);
}

void MGE::ColliderComponent::setDensity(float density) const
{
    _fixture->SetDensity(density);
}

void MGE::ColliderComponent::setFriction(float friction) const
{
    _fixture->SetFriction(friction);
}

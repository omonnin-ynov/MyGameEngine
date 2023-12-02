#include "ColliderComponent.h"

#include "Application.h"

void Update() {

}

MGE::ColliderComponent::ColliderComponent(std::string name) : AComponent(name), _fixtureDef()
{
}


void MGE::ColliderComponent::createFixture(b2Body& body)
{
    body.CreateFixture(&_fixtureDef);
}

void MGE::ColliderComponent::setDensity(float density)
{
    _fixture->SetDensity(density);
}

void MGE::ColliderComponent::setFriction(float friction)
{
    _fixture->SetFriction(friction);
}

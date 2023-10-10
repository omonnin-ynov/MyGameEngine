#include "AComponent.h"

unsigned int MGE::AComponent::createID()
{
    return 0;
}

MGE::AComponent::AComponent(std::string name)
{
    _ID = createID();
}

void MGE::AComponent::Awake()
{
}

void MGE::AComponent::Start()
{
}

void MGE::AComponent::Update()
{
}

void MGE::AComponent::LateUpdate()
{
}

unsigned int MGE::AComponent::getID()
{
    return _ID;
}

#include "AComponent.h"
#include "Application.h"

unsigned int MGE::AComponent::createID()
{
    return 0;
}

MGE::AComponent::AComponent()
{
    _ID = Application::getInstance()->GenerateID();
    _name = "";
}

MGE::AComponent::AComponent(std::string name = "")
{
    _ID = Application::getInstance()->GenerateID();
    _name = name;
}

void MGE::AComponent::Awake()
{
}

void MGE::AComponent::Start()
{
}

void MGE::AComponent::Update(float deltaTime)
{
}

void MGE::AComponent::LateUpdate(float deltaTime)
{
}

unsigned int MGE::AComponent::getID()
{
    return _ID;
}

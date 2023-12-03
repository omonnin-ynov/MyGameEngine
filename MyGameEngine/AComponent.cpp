#include "AComponent.h"
#include "Application.h"

MGE::AComponent::AComponent()
{
    _ID = Application::getInstance()->GenerateID();
    _name = "";
}

MGE::AComponent::AComponent(std::string name) : _name(name)
{
    _ID = Application::getInstance()->GenerateID();
}

uint64_t MGE::AComponent::getID() const
{
    return _ID;
}

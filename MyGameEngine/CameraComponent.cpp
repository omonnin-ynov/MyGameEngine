#include "CameraComponent.h"
#include "Application.h"

MGE::CameraComponent::CameraComponent(std::string name)
{
    _camera = new sf::View();
    _rotationFollowsParent = false;
}

MGE::CameraComponent::CameraComponent(std::string name, float x, float y, float halfSizeX, float halfSizeY, bool rotationFollowsParent)
{
    _camera = new sf::View(sf::Vector2f(x, y), sf::Vector2f(halfSizeX, halfSizeY));
    _rotationFollowsParent = rotationFollowsParent;
}

void MGE::CameraComponent::LateUpdate(float deltaTime)
{
    AEntity* parent = Application::getInstance()->getParentComponent(this);
    _camera->setCenter(parent->getPosition());
    if (_rotationFollowsParent) {
        _camera->setRotation(parent->getRotation());
    }
}

sf::View* MGE::CameraComponent::getView()
{
    return _camera;
}

void MGE::CameraComponent::setCameraZoom(float halfSizeX, float halfSizeY)
{
    _camera->setSize(halfSizeX, halfSizeY);
}

void MGE::CameraComponent::setCameraRotation(float angle)
{
    _camera->setRotation(angle);
}

void MGE::CameraComponent::setViewport(float x, float y, float z, float w)
{
    _camera->setViewport(sf::FloatRect(x, y, z, w));
}

void MGE::CameraComponent::setCameraRotationFollowsParent(bool rotationFollowsParent)
{
    _rotationFollowsParent = rotationFollowsParent;
}

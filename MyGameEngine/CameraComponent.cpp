#include "CameraComponent.h"

MGE::CameraComponent::CameraComponent(std::string name, float x, float y, float halfSizeX, float halfSizeY, bool rotationFollowsParent)
{
	sf::View _camera{sf::Vector2f(x, y), sf::Vector2f(halfSizeX, halfSizeY)};
	_rotationFollowsParent = rotationFollowsParent;
}

void MGE::CameraComponent::Update(float deltaTime)
{

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

#pragma once
#include "AComponent.h"
#include <SFML/Graphics.hpp>

namespace MGE {
	class CameraComponent : public AComponent
	{
	protected:
		sf::View* _camera;
		bool _rotationFollowsParent;

	public:
		CameraComponent(std::string name, float x, float y, float halfSizeX, float halfSizeY, bool rotationFollowsParent);

		void Update(float deltaTime) override;

		sf::View* getView();

		void setCameraZoom(float halfSizeX, float halfSizeY);
		void setCameraRotation(float angle);
		void setViewport(float x, float y, float z, float w);
		void setCameraRotationFollowsParent(bool rotationFollowsParent);
	};
}

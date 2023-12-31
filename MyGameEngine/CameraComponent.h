#pragma once
#include "AComponent.h"
#include <SFML/Graphics.hpp>

namespace MGE {
    class CameraComponent : public AComponent
    {
    protected:
        sf::View _camera;
        bool _rotationFollowsParent;

    public:
        CameraComponent(std::string name);
        CameraComponent(std::string name, float x, float y, float halfSizeX, float halfSizeY, bool rotationFollowsParent);

        void Awake() override;
        void Start() override;
        void Update(float deltaTime) override;
        void LateUpdate(float deltaTime) override;

        sf::View* getView();

        sf::Vector2f getCameraViewportSize();
        void setCameraZoom(float halfSizeX, float halfSizeY);
        void setCameraRotation(float angle);
        void setViewport(float x, float y, float z, float w);
        void setCameraRotationFollowsParent(bool rotationFollowsParent);
    };
}

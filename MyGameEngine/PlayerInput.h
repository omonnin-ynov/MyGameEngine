#pragma once
#include "AComponent.h"

namespace MGE
{
    class PlayerInput :
        public AComponent
    {
    protected:
        const sf::Vector2f _movementMultiplier{300.0f, 300.0f};
    public:
        PlayerInput(std::string name);
        void Update(float deltaTime) override;
    };
}

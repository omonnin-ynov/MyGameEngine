#pragma once
#include "AComponent.h"

namespace MGE
{
    class PlayerInput :
        public AComponent
    {
    protected:
        const sf::Vector2f _movementMultiplier{100.0f, 100.0f};
    public:
        void Update(float deltaTime) override;
    };
}

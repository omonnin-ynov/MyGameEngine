#pragma once

#include <SFML/Graphics.hpp>
#include "AComponent.h"

namespace MGE {
    /// used for testing
    class CircleComponent : public AComponent, public sf::Drawable
    {
    protected:
        float _offsetX;
        float _offsetY;
    public:
        CircleComponent(std::string name);

        void Awake() override;
        void Start() override;
        void Update(float deltaTime) override;
        void LateUpdate(float deltaTime) override;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

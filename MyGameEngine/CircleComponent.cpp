#include "CircleComponent.h"

void MGE::CircleComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    states.transform.translate(_offsetX, _offsetY);
    target.draw(shape, states);
}

MGE::CircleComponent::CircleComponent(std::string name)
{
    _offsetX = 0;
    _offsetY = 0;
}

void MGE::CircleComponent::Awake()
{
}

void MGE::CircleComponent::Start()
{
}

void MGE::CircleComponent::Update(float deltaTime)
{
}

void MGE::CircleComponent::LateUpdate(float deltaTime)
{
}


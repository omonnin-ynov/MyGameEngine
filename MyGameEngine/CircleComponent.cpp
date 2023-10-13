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

void MGE::CircleComponent::Update(float deltaTime)
{
	_offsetX = 0.01f * std::rand();
	_offsetY = 0.01f * std::rand();
}


#pragma once

#include <SFML/Graphics.hpp>
#include "AComponent.h"

namespace MGE {
	class CircleComponent : public AComponent, public sf::Drawable
	{
	protected:
		float _offsetX;
		float _offsetY;
	public:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		CircleComponent(std::string name);
		virtual void Update(float deltaTime) override;
	};
}

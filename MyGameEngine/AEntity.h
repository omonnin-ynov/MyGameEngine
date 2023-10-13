#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "AComponent.h"

namespace MGE {
	class AEntity : public sf::Transformable, public sf::Drawable {
	protected:
		unsigned int _ID;
		std::string _name;
		std::vector<AComponent*> _components;

	public:
		AEntity();
		AEntity(std::string name);
		AEntity(std::string name, float x, float y);

		virtual void Awake();
		virtual void Start();
		virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);

		const std::vector<AComponent*> getComponents();
		void attachComponent(AComponent* component);

		unsigned int getID();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		std::string E();
	};
}


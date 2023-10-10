#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "AComponent.h"

namespace MGE {
	class AEntity : public sf::Transformable, public sf::Drawable {
	protected:
		unsigned int _ID;
		std::string _name;
		std::list<AComponent> _components;

	public:
		AEntity(std::string name);

		void Awake();
		void Start();
		void Update();
		void LateUpdate();

		const std::list<AComponent> getComponents();
		void attachComponent(AComponent component);

		unsigned int getID();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		std::string E();
	};
}


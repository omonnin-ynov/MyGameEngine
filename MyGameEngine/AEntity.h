#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "AComponent.h"

namespace MGE {
	class AEntity : public sf::Transformable, public sf::Drawable {
	protected:
		unsigned int _ID;
		std::string _name;
		std::list<AComponent> components;

	public:
		AEntity(std::string name);
		virtual void Awake() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		unsigned int getID();
		std::string E();
	};
}


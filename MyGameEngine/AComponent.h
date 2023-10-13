#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace MGE {
	class AComponent {
	protected:
		unsigned int _ID;
		unsigned int createID();
		std::string _name;

	public:
		AComponent();
		AComponent(std::string name);
		virtual void Awake();
		virtual void Start();
		virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);
		unsigned int getID();
	};
}

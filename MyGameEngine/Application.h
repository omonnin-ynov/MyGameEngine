#pragma once
#include "AEntity.h"
#include <SFML/Graphics.hpp>

namespace MGE {
	class Application {
	private:
		unsigned int _IDCounter;
		std::list<AEntity> _entities;
		sf::RenderWindow* _window;

	public:
		Application();

		void start();

		void exit();

		void initalizeWindow(int x, int y);

		void update();

		void draw();

		MGE::AEntity createEntity(std::string name);

		MGE::AComponent createComponent();

		MGE::AComponent createComponentAndAttach(MGE::AEntity entity);

		const sf::RenderWindow* getWindow() {
			if (_window->isOpen()) {
				return _window;
			}
			std::cerr << "warning: getWindow was called with no active window";
			return nullptr;
		}
	};
}
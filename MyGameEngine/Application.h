#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "AEntity.h"

namespace MGE {
	class Application {
	protected:
		
		unsigned int _IDCounter;
		static Application* _instance;

		std::map<unsigned int, AEntity*> _entities;
		std::map<unsigned int, AComponent*> _components;
		std::map<unsigned int, unsigned int> _compToEntityLink;

		sf::RenderWindow* _window;
		bool _shouldExit;
		AEntity* _activeCameraEntity;
		Application();

	public:

		static Application* getInstance();

		void start();

		void initalizeWindow(int x, int y);

		void update(float deltaTime);

		void handleInput();

		unsigned int GenerateID();

		const sf::RenderWindow* getWindow();

		const sf::View* getActiveCamera();

		void setActiveCamera(AEntity* cameraEntity);

		AEntity* getEntityFromID(unsigned int ID);

		AComponent* getComponentFromID(unsigned int ID);

		AEntity* getParentComponent(AComponent* comp);

		template <std::derived_from<AEntity> T>
		T* createEntity(std::string name)
		{
			T* newEntity = new T(name);
			_entities[newEntity->getID()] = newEntity;
			return newEntity;
		}

		template <std::derived_from<AComponent> T>
		T* createComponent(std::string name)
		{
			T* newComp = new T(name);
			_components[newComp->getID()] = newComp;
			return newComp;
		}

		template <std::derived_from<AComponent> T>
		T* createComponentAndAttach(std::string name, MGE::AEntity* entity)
		{
			T* newComp = new T(name);
			_components[newComp->getID()] = newComp;
			_compToEntityLink[newComp->getID()] = entity->getID();
			entity->attachComponent(newComp);
			return newComp;
		}
	};
}

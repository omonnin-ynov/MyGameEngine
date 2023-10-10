#include "pch.h"
#include "Application.h"
#include <iostream>
#include <list>

// TODO error handling

/// <summary>
/// Create Application with IDCounter = 0 and empty list of entities
/// WARNING: window is nullptr before InitalizeWindow
/// </summary>
MGE::Application::Application()
{
	_IDCounter = 0;
	_entities = std::list<AEntity>();
	_window = nullptr;
}

void MGE::Application::start()
{
}

void MGE::Application::exit()
{
}

/// <summary>
/// Initialize a new window and assign it to member variable
/// If a window already existed, close it
/// </summary>
void MGE::Application::initalizeWindow(int x, int y)
{
	if (_window) {
		_window->close();
		
	}
	_window = &(sf::RenderWindow::RenderWindow(sf::VideoMode(x, y), "Window created"));
	// TODO error handling
}

void MGE::Application::update()
{
}

void MGE::Application::draw()
{
}

// TODO handle IDs
MGE::AEntity MGE::Application::createEntity(std::string name)
{
	AEntity newEntity = MGE::AEntity(name);
	_entities.push_back(newEntity);
	return newEntity;
}

MGE::AComponent MGE::Application::createComponent()
{
	return MGE::AComponent();
}

MGE::AComponent MGE::Application::createComponentAndAttach(MGE::AEntity entity)
{
	AComponent newComponent = AComponent();
	entity.attachComponent(newComponent);

}

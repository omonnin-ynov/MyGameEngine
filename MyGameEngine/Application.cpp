#include <vector>
#include <algorithm>
#include "pch.h"
#include "Application.h"
#include "CameraComponent.h"

MGE::Application* MGE::Application::_instance = nullptr;

/// <summary>
/// Create Application with IDCounter = 0 and empty list of entities
/// WARNING: window is nullptr before InitalizeWindow
/// </summary>
MGE::Application::Application() : _entities(), _components(), _compToEntityLink()
{
    _IDCounter = 0;
    _window = nullptr;
    _shouldExit = false;
}

MGE::Application* MGE::Application::getInstance()
{
    if (!_instance) {
        _instance = new Application();
    }
    return _instance;
}

void MGE::Application::start()
{
    if (_window) {
        sf::Clock clock;
        while (!_shouldExit) {
            // handleInput();
            float deltaTime = clock.restart().asSeconds();
            update(deltaTime);
        }
    }
    else {
        std::cout << "No window is active currently";
    }
}

/// <summary>
/// Initialize a new window and assign it to member variable
/// If a window already existed, close it
/// </summary>
void MGE::Application::initalizeWindow(int x, int y)
{
    if (_window && _window->isOpen()) {
        _window->close();
        delete _window;
    }
    _window = new sf::RenderWindow(sf::VideoMode(x, y), "Window created");
    // TODO error handling
}

void MGE::Application::update(float deltaTime)
{
    for (auto& [key, value] : _entities) {
        value->Update(deltaTime);
    }

    for (auto& [key, value] : _entities) {
        value->LateUpdate(deltaTime);
    }

    _window->setView(*_activeCameraComponent->getView());
    _window->clear();

    for (auto& [key, value] : _entities) {
        if (_entities.find(key) != _entities.end()) {
            _window->draw(*_entities[key]);
        }
    }
    _window->display();
}

void MGE::Application::handleInput()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Event inputEvent;
    while (_window->pollEvent(inputEvent)) {
        if (inputEvent.type == sf::Event::Closed()) {
            _window->close();
            _shouldExit = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        shape.setPosition(shape.getPosition() + sf::Vector2f(0.0f, 0.5f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        shape.setPosition(shape.getPosition() + sf::Vector2f(0.0f, -0.5f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        shape.setPosition(shape.getPosition() + sf::Vector2f(0.5f, 0.0f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        shape.setPosition(shape.getPosition() + sf::Vector2f(-0.5f, 0.0f));
    }
    _window->draw(shape);
}

uint64_t MGE::Application::GenerateID()
{
    _IDCounter++;
    return _IDCounter;
}

sf::RenderWindow* MGE::Application::getWindow()
{
    if (_window->isOpen()) {
        return _window;
    }
    std::cout << "warning: getWindow was called with no active window";
    return nullptr;
}

sf::View* MGE::Application::getActiveCamera()
{
    return nullptr;
}

/// <summary>
/// Will set the cameraComponent of entity as active for the current window.
/// Will grab the first CameraComponent it encounters. Does nothing if entity has no CameraComponent.
/// </summary>
/// <param name="cameraEntity"></param>
void MGE::Application::setActiveCamera(AEntity* cameraEntity)
{
    for (AComponent* comp : cameraEntity->getComponents()) {
        auto cameraComp = dynamic_cast<CameraComponent*>(comp);
        if (cameraComp) {
            _window->setView(*(cameraComp->getView()));
            _activeCameraComponent = cameraComp;
            return;
        }
    }
    return;
}

MGE::AEntity* MGE::Application::getEntityFromID(uint64_t ID)
{
    if (_entities.find(ID) != _entities.end()) {
        return _entities[ID];
    }
    return nullptr;
}

MGE::AComponent* MGE::Application::getComponentFromID(uint64_t ID)
{
    if (_components.find(ID) != _components.end()) {
        return _components[ID];
    }
    return nullptr;
}

/// <summary>
/// Finds the component's parent. Returns nullptr if no parent component.
/// </summary>
/// <param name="comp">The component whose parent will be retrieved.</param>
/// <returns>The parent component. Nullptr if nonexistent.</returns>
MGE::AEntity* MGE::Application::getParentComponent(AComponent* comp)
{
    try {
        uint64_t ID = _compToEntityLink.at(comp->getID());
        return _entities[ID];
    }
    catch (std::out_of_range) {
        return nullptr;
    }
    return nullptr;
}

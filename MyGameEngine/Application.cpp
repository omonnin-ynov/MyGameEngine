#include <vector>
#include <algorithm>
#include "pch.h"
#include "Application.h"
#include "BoxCollider.h"
#include "CameraComponent.h"
#include "RigidBodyComponent.h"
#include "SpriteRendererComponent.h"

MGE::Application* MGE::Application::_instance = nullptr;

std::map<b2Body*, MGE::RigidBodyComponent*>* MGE::Application::getb2BodyToComp()
{
	return &_b2BodyToComp;
}

/// <summary>
/// Create Application with IDCounter = 0 and empty list of entities
/// WARNING: window is nullptr before InitalizeWindow
/// </summary>
MGE::Application::Application() : _physics(b2Vec2(0.0f, 0.0f)), _luaSystem(), _entities(), _components(),
                                  _compToEntityLink()
{
    _IDCounter = 0;
    _window = nullptr;
    _shouldExit = false;

    std::random_device rd;
    std::seed_seq sd{ rd(), rd(), rd(), rd() };
    _rng = std::mt19937(sd);
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
            handleInput();
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
}

/// \brief Runs the main update loop in order:
/// Update, physics update, LateUpdate, Draw, Display, Delete dirty entities/components
/// \param deltaTime time since last update
void MGE::Application::update(float deltaTime)
{
    for (auto& [key, value] : _entities) {
        value->Update(deltaTime);
    }

    // run in separate thread if fixedUpdate is needed
    _physics.Update(deltaTime);

    for (auto& [key, value] : _entities) {
        value->LateUpdate(deltaTime);
    }

    if (_activeCameraComponent && _activeCameraComponent->getView()) {
        _window->setView(*_activeCameraComponent->getView());
    }
    _window->clear();

    for (auto& [key, value] : _entities) {
        _window->draw(*value);
    }
    _window->display();

    for (uint64_t ID : _toBeDeleted)
    {
        auto entityIterator = _entities.find(ID);
        if (entityIterator != _entities.end())
        {
            destroyEntity(entityIterator->second);
        }
        auto compIterator = _components.find(ID);
        if (compIterator != _components.end())
        {
            destroyComponent(compIterator->second);
        }
    }
    _toBeDeleted.clear();
}

void MGE::Application::handleInput()
{
    sf::Event inputEvent;
    while (_window->pollEvent(inputEvent)) {
        if (inputEvent.type == sf::Event::Closed()) {
            _window->close();
            _shouldExit = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    }
}

uint64_t MGE::Application::GenerateID()
{
    _IDCounter++;
    return _IDCounter;
}

std::map<uint64_t, MGE::AEntity*>* MGE::Application::getEntities()
{
    return &_entities;
}

std::map<uint64_t, MGE::AComponent*>* MGE::Application::getComponents()
{
    return &_components;
}

MGE::PhysicsSystem& MGE::Application::getPhysics()
{
    return _physics;
}

b2World* MGE::Application::getWorld()
{
    return _physics.getWorld();
}

MGE::LuaSystem* MGE::Application::getLua()
{
    return &_luaSystem;
}

sf::RenderWindow* MGE::Application::getWindow() const
{
    if (_window->isOpen()) {
        return _window;
    }
    std::cout << "warning: getWindow was called with no active window";
    return nullptr;
}

MGE::CameraComponent* MGE::Application::getActiveCamera() const
{
    return _activeCameraComponent;
}

/// <summary>
/// Sets the camera component as main camera
/// </summary>
void MGE::Application::setActiveCamera(CameraComponent* cameraComp)
{
    _window->setView(*(cameraComp->getView()));
    _activeCameraComponent = cameraComp;
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
MGE::AEntity* MGE::Application::getParentEntity(AComponent* comp)
{
    try {
        uint64_t ID = _compToEntityLink.at(comp->getID());
        return _entities[ID];
    }
    catch (std::out_of_range) {
        return nullptr;
    }
}

int MGE::Application::getRand()
{
    return _rng();
}

void MGE::Application::registerEntity(AEntity* entity)
{
    _entities[entity->getID()] = entity;
}

void MGE::Application::registerEntityAndAttachedComponents(AEntity* entity)
{
    _entities[entity->getID()] = entity;
    for (AComponent* comp : *entity->getComponents())
    {
        _components[comp->getID()] = comp;
        _compToEntityLink[comp->getID()] = entity->getID();
    }
}

/// \brief Destroys entity and all attached components
/// \param entity entity to be destroyed
void MGE::Application::destroyEntity(MGE::AEntity* entity)
{
    std::vector<MGE::AComponent*> components = *entity->getComponents();
    for (int i = 0; i < components.size(); i++)
    {
        destroyComponent(components[i]);
    }
    auto entityIterator = _entities.find(entity->getID());
    if (entityIterator != _entities.end())
    {
        _entities.erase(entityIterator);
    }
    delete entity;
}

void MGE::Application::registerComponent(AComponent* comp, MGE::AEntity* parent)
{
    _components[comp->getID()] = comp;
    _compToEntityLink[comp->getID()] = parent->getID();
    parent->attachComponent(comp);
}

void MGE::Application::destroyComponent(MGE::AComponent* comp)
{
    auto linkIterator = _compToEntityLink.find(comp->getID());
    if (linkIterator != _compToEntityLink.end())
    {
        auto attachedEntity = _entities[linkIterator->second];
        attachedEntity->detachComponent(comp);
        _compToEntityLink.erase(comp->getID());
    }
    auto compIterator = _components.find(comp->getID());
    if (compIterator != _components.end())
    {
        _components.erase(comp->getID());
    }
    delete comp;
}

void MGE::Application::markForDeletion(uint64_t ID)
{
    _toBeDeleted.push_back(ID);
}

/// \brief create spriteRenderer, Collider and RigidBody components for the given entity.
/// Since there are many such entities of this type in games, this is a straightforward way to instantiate one.
/// The collider size is set to the sprite size and divided by the physics world scale
/// \param parent Entity for which the components will be created
/// \param textureName Texture to set for the sprite
/// \param bodyType dynamic, static or kinematic body (according to b2bodyType)
/// \param isSensor Is the collider a sensor https://box2d.org/documentation/classb2_fixture.html#aedd23d27ff7ce2d53b6c5b7a878a35d3
/// \param collisionGroup Which collision group the collider belongs to https://box2d.org/documentation/md__d_1__git_hub_box2d_docs_dynamics.html#autotoc_md79
/// \param collisionMask Which collision groups can the collider collide with https://box2d.org/documentation/md__d_1__git_hub_box2d_docs_dynamics.html#autotoc_md79
void MGE::Application::createSpriteAndPhysicsComponents(AEntity* parent, sf::Texture& texture,
                                                        b2BodyType bodyType, bool isSensor, uint16 collisionGroup, uint16 collisionMask)
{
    auto Sprite = new SpriteRendererComponent(parent->getName() + "Sprite");
    Sprite->setTexture(texture);

    auto RigidBody = new RigidBodyComponent(parent->getName() + "RigidBody");
    RigidBody->setBodyType(bodyType);

    b2FixtureDef fixtureDef = b2FixtureDef();
    fixtureDef.isSensor = isSensor;
    fixtureDef.filter.categoryBits = collisionGroup;
    fixtureDef.filter.maskBits = collisionMask;
    sf::IntRect spriteSize = Sprite->getSprite().getTextureRect();
    b2PolygonShape box{};
    box.SetAsBox(spriteSize.width / PhysicsSystem::WorldScale, spriteSize.height / PhysicsSystem::WorldScale);
    fixtureDef.shape = &box;

    auto Collider = new BoxCollider(parent->getName() + "Collider", fixtureDef);
    Collider->createFixture(*RigidBody->getBody());

    parent->attachComponent(Sprite);
    parent->attachComponent(RigidBody);
    parent->attachComponent(Collider);
}

#include "PhysicsSystem.h"
#include "Application.h"
#include "RigidBodyComponent.h"

using namespace MGE;

PhysicsSystem::PhysicsSystem(b2Vec2 gravity) : _world(gravity)
{
    _world.SetContactListener(&_collisionListener);
}

void PhysicsSystem::Update(float deltaTime)
{
    auto app = Application::getInstance();
    std::map<uint64_t, AEntity*>* entities = app->getEntities();
    std::map<uint64_t, AComponent*>* components = app->getComponents();

    for (auto [ID, entity] : *entities) {
        for (auto comp : *entity->getComponents()) {
            auto rigidBodyComp = dynamic_cast<RigidBodyComponent*>(comp);

            if (rigidBodyComp) {
                sf::Vector2f pos = entity->getPosition();
                float angle = entity->getRotation();
                rigidBodyComp->setTransform(b2Vec2(pos.x / WorldScale, pos.y / WorldScale), angle * (b2_pi / 180.0f));
            }
        }
    }

    _world.Step(deltaTime, 8, 3);

    for (auto [ID, entity] : *entities) {
        for (auto comp : *entity->getComponents()) {
            auto rigidBodyComp = dynamic_cast<RigidBodyComponent*>(comp);

            if (rigidBodyComp) {
                b2Vec2 pos = rigidBodyComp->getPosition();
                entity->setPosition(sf::Vector2(pos.x * WorldScale, pos.y * WorldScale));
                float angle = rigidBodyComp->getAngle();
                entity->setRotation(angle * (180.0f / b2_pi));
            }
        }
    }
}

b2World* PhysicsSystem::getWorld()
{
    return &_world;
}

void PhysicsSystem::setGravity(b2Vec2 gravity)
{
    _world.SetGravity(gravity);
}

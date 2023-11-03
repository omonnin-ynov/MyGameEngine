#include "CollisionListener.h"
#include "Application.h"
#include "ICollidable.h"
#include "RigidBodyComponent.h"

void MGE::CollisionListener::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    auto entities = *Application::getInstance()->getEntities();

    for (auto [ID, entity] : entities) {
        std::vector<ICollidable*> collidableComps{};
        RigidBodyComponent* rigidBody = nullptr;

        for (auto comp : entity->getComponents()) {
            auto collidable = dynamic_cast<ICollidable*>(comp);
            auto rigidBodyTest = dynamic_cast<RigidBodyComponent*>(comp);

            if (collidable) {
                collidableComps.push_back(collidable);
            }
            if (rigidBodyTest && (rigidBodyTest->getBody() == bodyA || rigidBodyTest->getBody() == bodyB)) {
                rigidBody = rigidBodyTest;
            }
        }
        if (collidableComps.size() > 0 && rigidBody) {
            for (ICollidable* collidable : collidableComps) {
                collidable->BeginCollision(contact);
            }
        }
    }
}

void MGE::CollisionListener::EndContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    auto entities = *Application::getInstance()->getEntities();

    for (auto [ID, entity] : entities) {
        std::vector<ICollidable*> collidableComps{};
        RigidBodyComponent* rigidBody = nullptr;

        for (auto comp : entity->getComponents()) {
            auto collidable = dynamic_cast<ICollidable*>(comp);
            auto rigidBodyTest = dynamic_cast<RigidBodyComponent*>(comp);

            if (collidable) {
                collidableComps.push_back(collidable);
            }
            if (rigidBodyTest && (rigidBodyTest->getBody() == bodyA || rigidBodyTest->getBody() == bodyB)) {
                rigidBody = rigidBodyTest;
            }
        }
        if (collidableComps.size() > 0 && rigidBody) {
            for (ICollidable* collidable : collidableComps) {
                collidable->EndCollision(contact);
            }
        }
    }
}

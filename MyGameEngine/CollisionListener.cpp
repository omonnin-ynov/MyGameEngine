#include "CollisionListener.h"
#include "Collision.h"
#include "Application.h"
#include "ICollidable.h"
#include "RigidBodyComponent.h"

void MGE::CollisionListener::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    auto entities = *Application::getInstance()->getEntities();

    for (auto entity : entities | std::views::values) {
        std::vector<ICollidable*> collidableComps{};
        RigidBodyComponent* rigidBody = nullptr;

        for (auto comp : *entity->getComponents()) {
            auto collidable = dynamic_cast<ICollidable*>(comp);
            auto rigidBodyTest = dynamic_cast<RigidBodyComponent*>(comp);

            if (collidable) {
                collidableComps.push_back(collidable);
            }
            if (rigidBodyTest && (rigidBodyTest->getBody() == bodyA || rigidBodyTest->getBody() == bodyB)) {
                rigidBody = rigidBodyTest;
            }
        }
        if (!collidableComps.empty() && rigidBody) {
            for (ICollidable* collidable : collidableComps) {
                collidable->BeginCollision(Collision(rigidBody->getBody(), rigidBody->getBody() == bodyA ? bodyA : bodyB));
            }
        }
    }
}

void MGE::CollisionListener::EndContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    auto entities = *Application::getInstance()->getEntities();

    for (auto entity : entities | std::views::values) {
        std::vector<ICollidable*> collidableComps{};
        RigidBodyComponent* rigidBody = nullptr;

        for (auto comp : *entity->getComponents()) {
            auto collidable = dynamic_cast<ICollidable*>(comp);
            auto rigidBodyTest = dynamic_cast<RigidBodyComponent*>(comp);

            if (collidable) {
                collidableComps.push_back(collidable);
            }
            if (rigidBodyTest && (rigidBodyTest->getBody() == bodyA || rigidBodyTest->getBody() == bodyB)) {
                rigidBody = rigidBodyTest;
            }
        }
        if (!collidableComps.empty() && rigidBody) {
            for (ICollidable* collidable : collidableComps) {
                collidable->EndCollision(Collision(rigidBody->getBody(), rigidBody->getBody() == bodyA ? bodyA : bodyB));
            }
        }
    }
}

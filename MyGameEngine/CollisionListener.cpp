#include "CollisionListener.h"
#include "Collision.h"
#include "Application.h"
#include "ICollidable.h"
#include "RigidBodyComponent.h"

void MGE::CollisionListener::BeginContact(b2Contact* contact)
{
    auto app = Application::getInstance();

    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    RigidBodyComponent* rigidBodyA = (*app->getb2BodyToComp())[bodyA];
    AEntity* parentA = app->getParentEntity(rigidBodyA);

    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    RigidBodyComponent* rigidBodyB = (*app->getb2BodyToComp())[bodyB];
    AEntity* parentB = app->getParentEntity(rigidBodyB);

    if(auto collidable = dynamic_cast<ICollidable*>(rigidBodyA))
    {
        collidable->BeginCollision(Collision(bodyA, rigidBodyA, parentA, bodyB, rigidBodyB, parentB));
    }

    for (auto comp : *parentA->getComponents())
    {
        if (auto collidable = dynamic_cast<ICollidable*>(comp))
        {
            collidable->BeginCollision(Collision(bodyA, rigidBodyA, parentA, bodyB, rigidBodyB, parentB));
        }
    }

    if (auto collidable = dynamic_cast<ICollidable*>(rigidBodyB))
    {
        collidable->BeginCollision(Collision(bodyB, rigidBodyB, parentB, bodyA, rigidBodyA, parentA));
    }

    for (auto comp : *parentB->getComponents())
    {
        if (auto collidable = dynamic_cast<ICollidable*>(comp))
        {
            collidable->BeginCollision(Collision(bodyB, rigidBodyB, parentB, bodyA, rigidBodyA, parentA));
        }
    }
}

void MGE::CollisionListener::EndContact(b2Contact* contact)
{
    auto app = Application::getInstance();

    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    RigidBodyComponent* rigidBodyA = (*app->getb2BodyToComp())[bodyA];
    AEntity* parentA = app->getParentEntity(rigidBodyA);

    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    RigidBodyComponent* rigidBodyB = (*app->getb2BodyToComp())[bodyB];
    AEntity* parentB = app->getParentEntity(rigidBodyB);

    if (auto collidable = dynamic_cast<ICollidable*>(rigidBodyA))
    {
        collidable->EndCollision(Collision(bodyA, rigidBodyA, parentA, bodyB, rigidBodyB, parentB));
    }

    for (auto comp : *parentA->getComponents())
    {
        if (auto collidable = dynamic_cast<ICollidable*>(comp))
        {
            collidable->EndCollision(Collision(bodyA, rigidBodyA, parentA, bodyB, rigidBodyB, parentB));
        }
    }

    if (auto collidable = dynamic_cast<ICollidable*>(rigidBodyB))
    {
        collidable->EndCollision(Collision(bodyB, rigidBodyB, parentB, bodyA, rigidBodyA, parentA));
    }

    for (auto comp : *parentB->getComponents())
    {
        if (auto collidable = dynamic_cast<ICollidable*>(comp))
        {
            collidable->EndCollision(Collision(bodyB, rigidBodyB, parentB, bodyA, rigidBodyA, parentA));
        }
    }
}

#include "CollisionListener.h"
#include "Collision.h"
#include "Application.h"
#include "ICollidable.h"
#include "RigidBodyComponent.h"

void MGE::CollisionListener::BeginContact(b2Contact* contact)
{
    auto app = Application::getInstance();

    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    RigidBodyComponent* rigidBodyA;
    RigidBodyComponent* rigidBodyB;

    // Cancel contact if one of the entities was deleted
    // Box2d will trigger endCollision when a RigidBody is destroyed, for example
    try
    {
        rigidBodyA = app->getb2BodyToComp()->at(bodyA);
        rigidBodyB = app->getb2BodyToComp()->at(bodyB);
    }
    catch (std::out_of_range& ) {
        return;
    }
    AEntity* parentA = app->getParentEntity(rigidBodyA);
    AEntity* parentB = app->getParentEntity(rigidBodyB);

    if (parentA->getName() == "simon" || parentB->getName() == "simon")
    {
        auto test = 10;
    }

    if(auto collidable = dynamic_cast<ICollidable*>(parentA))
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

    if (auto collidable = dynamic_cast<ICollidable*>(parentB))
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
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    RigidBodyComponent* rigidBodyA;
    RigidBodyComponent* rigidBodyB;

    // Cancel contact if one of the entities was deleted
	// Box2d will trigger endCollision when a RigidBody is destroyed, for example
    try
    {
        rigidBodyA = app->getb2BodyToComp()->at(bodyA);
        rigidBodyB = app->getb2BodyToComp()->at(bodyB);
    } catch (std::out_of_range& ) {
        return;
    }
    AEntity* parentA = app->getParentEntity(rigidBodyA);
    AEntity* parentB = app->getParentEntity(rigidBodyB);

    if (auto collidable = dynamic_cast<ICollidable*>(parentA))
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

    if (auto collidable = dynamic_cast<ICollidable*>(parentB))
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

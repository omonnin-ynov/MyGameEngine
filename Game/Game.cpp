#include <SFML/Graphics.hpp>
#include <MyGameEngine/Application.h>
#include <MyGameEngine/ResourceManager.h>
#include <MyGameEngine/AEntity.h>
#include <MyGameEngine/SpriteRendererComponent.h>
#include <MyGameEngine/RigidBodyComponent.h>
#include <MyGameEngine/ColliderComponent.h>
#include <MyGameEngine/BoxCollider.h>
#include <MyGameEngine/CircleComponent.h>
#include <MyGameEngine/CameraComponent.h>

#include "Projectile.h"
#include "MyGameEngine/PlayerInput.h"
#include "TimedProjectileSpawner.h"

int main()
{
    MGE::Application* app = MGE::Application::getInstance();
    app->initalizeWindow(1280, 800);

    MGE::ResourceManager* resManager = MGE::ResourceManager::getInstance();

    auto player = app->createEntity<MGE::AEntity>("circle1");

    // TODO rotation still incorrect
    player->setPosition(0.0f, 0.0f);
    player->setRotation(-45.0f);
    auto InputComponent = app->createComponentAndAttach<MGE::PlayerInput>("playerInput", player);

    // Idée: le createComponent retourne une fonction d'init qu'il faut exécuter avant que le component soit prêt
    auto SpriteComp1 = app->createComponentAndAttach<MGE::SpriteRendererComponent>("spriteRenderer1", player);
    std::string awesomeTexturePath = resManager->getPathFromName("awesomeFace");
    SpriteComp1->loadAndSetTexture(awesomeTexturePath);

    auto rigidBodyComp = app->createComponentAndAttach<MGE::RigidBodyComponent>("rigidSphere", player);
    rigidBodyComp->setBodyType(b2BodyType::b2_staticBody);

    auto colliderComp = app->createComponentAndAttach<MGE::BoxCollider>("SphereCollider", player);
    //sf::Vector2f textureSize = SpriteComp1->getTexture().getSize() * SpriteComp1->getSprite().getScale();
    //colliderComp->setHalfSize(textureSize.x / 2.0f, textureSize.y / 2.0f);
    colliderComp->createFixture(*rigidBodyComp->getBody());

    auto TimedProjectileSpawner = app->createComponentAndAttach<ILM::TimedProjectileSpawner>("TimedProjectileSpawner", player);
    auto fireball = new ILM::Projectile("Fireball");

    auto fireballSprite = new MGE::SpriteRendererComponent("fireballSprite");
    fireballSprite->loadAndSetTexture(resManager->getPathFromName("fireball"));
    fireball->attachComponent(fireballSprite);

    //auto fireballRigidBody = app->createComponentAndAttach<MGE::RigidBodyComponent>("fireballRigidBody", fireball);
    //fireballRigidBody->setBodyType(b2BodyType::b2_staticBody);

    //auto fireballCollider = app->createComponentAndAttach<MGE::BoxCollider>("SphereCollider2", fireball);
    //fireballCollider->setHalfSize(12.0f, 4.0f);
    //fireballCollider->createFixture(*fireballRigidBody->getBody());

    TimedProjectileSpawner->addProjectile(fireball);

    auto circle2 = app->createEntity<MGE::AEntity>("circle2");
    auto SpriteComp2 = app->createComponentAndAttach<MGE::SpriteRendererComponent>("spriteRenderer2", circle2);

    std::string containerTexturePath = resManager->getPathFromName("container");
    SpriteComp2->loadAndSetTexture(containerTexturePath);

    auto rigidBodyComp2 = app->createComponentAndAttach<MGE::RigidBodyComponent>("rigidSphere2", circle2);
    rigidBodyComp2->setBodyType(b2BodyType::b2_staticBody);

    auto colliderComp2 = app->createComponentAndAttach<MGE::BoxCollider>("SphereCollider2", circle2);
    colliderComp2->setHalfSize(12.0f, 4.0f);
    colliderComp2->createFixture(*rigidBodyComp2->getBody());
    

    auto camera = app->createComponentAndAttach<MGE::CameraComponent>("Camera", player);
    camera->setCameraRotationFollowsParent(false);
    camera->setCameraZoom(2560, 1600);
    app->setActiveCamera(camera);

    app->start();

    return 0;
}

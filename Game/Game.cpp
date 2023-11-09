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

#include "MyGameEngine/PlayerInput.h"

int main()
{
    MGE::Application* app = MGE::Application::getInstance();
    app->initalizeWindow(1280, 800);

    MGE::ResourceManager* resManager = MGE::ResourceManager::getInstance();

    auto circle1 = app->createEntity<MGE::AEntity>("circle1");

    // TODO rotation still incorrect
    circle1->setPosition(0.0f, -1000.0f);
    circle1->setRotation(-45.0f);
    auto InputComponent = app->createComponentAndAttach<MGE::PlayerInput>("playerInput", circle1);
    // Idée: le createComponent retourne une fonction d'init qu'il faut exécuter avant que le component soit prêt
    auto SpriteComp1 = app->createComponentAndAttach<MGE::SpriteRendererComponent>("spriteRenderer1", circle1);

    std::string awesomeTexturePath = resManager->getPathFromName("awesomeFace");
    SpriteComp1->loadAndSetTexture(awesomeTexturePath);

    auto rigidBodyComp = app->createComponentAndAttach<MGE::RigidBodyComponent>("rigidSphere", circle1);
    rigidBodyComp->setBodyType(b2BodyType::b2_staticBody);

    auto colliderComp = app->createComponentAndAttach<MGE::BoxCollider>("SphereCollider", circle1);
    //sf::Vector2f textureSize = SpriteComp1->getTexture().getSize() * SpriteComp1->getSprite().getScale();
    //colliderComp->setHalfSize(textureSize.x / 2.0f, textureSize.y / 2.0f);
    colliderComp->createFixture(*rigidBodyComp->getBody());

    //auto circle2 = app->createEntity<MGE::AEntity>("circle2");
    //auto circleComp2 = app->createComponentAndAttach<MGE::CircleComponent>("circleComp2", circle2);

    auto circle2 = app->createEntity<MGE::AEntity>("circle2");
    auto SpriteComp2 = app->createComponentAndAttach<MGE::SpriteRendererComponent>("spriteRenderer2", circle2);

    std::string containerTexturePath = resManager->getPathFromName("container");
    SpriteComp2->loadAndSetTexture(containerTexturePath);

    auto rigidBodyComp2 = app->createComponentAndAttach<MGE::RigidBodyComponent>("rigidSphere2", circle2);
    rigidBodyComp2->setBodyType(b2BodyType::b2_staticBody);

    auto colliderComp2 = app->createComponentAndAttach<MGE::BoxCollider>("SphereCollider2", circle2);
    colliderComp2->setHalfSize(12.0f, 4.0f);
    colliderComp2->createFixture(*rigidBodyComp2->getBody());
    

    auto camera = app->createComponentAndAttach<MGE::CameraComponent>("Camera", circle1);
    camera->setCameraRotationFollowsParent(false);
    camera->setCameraZoom(2560, 1600);
    app->setActiveCamera(camera);

    app->start();

    return 0;
}

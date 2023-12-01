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
#include "GameManager.h"
#include "LuaProjectileMovement.h"
#include "Projectile.h"
#include "MyGameEngine/PlayerInput.h"
#include "TimedProjectileSpawner.h"

int main()
{
    MGE::Application* app = MGE::Application::getInstance();
    app->initalizeWindow(1280, 800);

    auto resManager = new ILM::ILMResourceManager();

    MGE::AEntity* player = resManager->instantiatePlayer("simon");

    // TODO rotation still incorrect
    player->setPosition(0.0f, -500.0f);
    auto InputComponent = app->createComponentAndAttach<MGE::PlayerInput>("playerInput", player);

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

#include <SFML/Graphics.hpp>
#include <MyGameEngine/Application.h>
#include <MyGameEngine/ResourceManager.h>
#include <MyGameEngine/AEntity.h>
#include <MyGameEngine/RigidBodyComponent.h>
#include <MyGameEngine/CameraComponent.h>
#include "GameManager.h"
#include "LuaProjectileMovement.h"
#include "MyGameEngine/PlayerInput.h"

int main()
{
    MGE::Application* app = MGE::Application::getInstance();
    app->initalizeWindow(1280, 800);

    auto resManager = new ILM::ILMResourceManager();

    app->getLua()->SetScript(resManager->getPathFromName("BouncyProjectile"));

    MGE::AEntity* player = resManager->instantiatePlayer("simon");

    player->setPosition(0.0f, -500.0f);
    auto InputComponent = app->createComponentAndAttach<MGE::PlayerInput>("playerInput", player);

    auto camera = app->createComponentAndAttach<MGE::CameraComponent>("Camera", player);
    camera->setCameraRotationFollowsParent(false);
    camera->setCameraZoom(2560, 1600);
    app->setActiveCamera(camera);

    app->start();

    return 0;
}

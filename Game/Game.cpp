#include <SFML/Graphics.hpp>
#include <MyGameEngine/Application.h>
#include <MyGameEngine/ResourceManager.h>
#include <MyGameEngine/AEntity.h>
#include <MyGameEngine/SpriteRendererComponent.h>
#include <MyGameEngine/CircleComponent.h>
#include <MyGameEngine/CameraComponent.h>

int main()
{
    MGE::Application* app = MGE::Application::getInstance();
    app->initalizeWindow(800, 800);

    MGE::ResourceManager* resManager = MGE::ResourceManager::getInstance();

    auto circle1 = app->createEntity<MGE::AEntity>("circle1");
    auto SpriteComp1 = app->createComponentAndAttach<MGE::SpriteRendererComponent>("spriteRenderer1", circle1);

    std::string awesomeTexturePath = resManager->getPathFromName("awesomeFace");
    SpriteComp1->loadAndSetTexture(awesomeTexturePath);

    auto circle2 = app->createEntity<MGE::AEntity>("circle2");
    auto circleComp2 = app->createComponentAndAttach<MGE::CircleComponent>("circleComp2", circle2);

    auto camera = app->createComponentAndAttach<MGE::CameraComponent>("Camera", circle1);
    camera->setCameraRotationFollowsParent(true);
    camera->setCameraZoom(1600, 1600);
    app->setActiveCamera(circle1);

    app->start();

    return 0;
}

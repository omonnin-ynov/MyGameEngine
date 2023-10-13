#include <SFML/Graphics.hpp>
#include <MyGameEngine/Application.h>
#include "Game.h"
#include <MyGameEngine/AEntity.h>
#include <MyGameEngine/CircleComponent.h>
#include <MyGameEngine/CameraComponent.h>

int main()
{
    MGE::Application* app = MGE::Application::getInstance();
    app->initalizeWindow(800, 800);

    auto circle1 = app->createEntity<MGE::AEntity>("circle1");
    auto circleComp1 = app->createComponentAndAttach<MGE::CircleComponent>("circleComp1", circle1);

    auto circle2 = app->createEntity<MGE::AEntity>("circle2");
    auto circleComp2 = app->createComponentAndAttach<MGE::CircleComponent>("circleComp2", circle2);

    auto camera = app->createComponentAndAttach<MGE::CameraComponent>("Camera", circle1);
    camera->setCameraRotationFollowsParent(true);
    camera->setCameraZoom(1600, 1600);
    app->setActiveCamera(circle1);

    app->start();

    return 0;
}

#include <SFML/Graphics.hpp>
#include <MyGameEngine/Application.h>
#include "Game.h"


int main()
{
    MGE::Application::Application();
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen())
    {
        sf::Event inputEvent;
        while (window.pollEvent(inputEvent)) {
            if (inputEvent.type == sf::Event::Closed()) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            shape.setPosition(shape.getPosition() + sf::Vector2f(0.0f, 0.5f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            shape.setPosition(shape.getPosition() + sf::Vector2f(0.0f, -0.5f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            shape.setPosition(shape.getPosition() + sf::Vector2f(0.5f, 0.0f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            shape.setPosition(shape.getPosition() + sf::Vector2f(-0.5f, 0.0f));
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
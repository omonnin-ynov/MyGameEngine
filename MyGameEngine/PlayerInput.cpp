#include "PlayerInput.h"
#include "Application.h"

MGE::PlayerInput::PlayerInput(std::string name)
{
}

void MGE::PlayerInput::Update(float deltaTime)
{
    sf::Vector2f movementAxis{ 0.0f, 0.0f };
    // Ca me paraît pas très beau comme manière de coder, mais vu la simplicité de l'input du joueur, ça semble être une solution acceptable
    // Pas de raison d'ajouter de la complexité
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        movementAxis.y -= _movementMultiplier.y;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        movementAxis.y += _movementMultiplier.y;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        movementAxis.x -= _movementMultiplier.x;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        movementAxis.x += _movementMultiplier.x;
    }
    Application::getInstance()->getParentEntity(this)->move(movementAxis * deltaTime);
}

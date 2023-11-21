#include "SpriteRendererComponent.h"
#include <format> 
#include <functional>
#include <iostream>
#include "ResourceManager.h"
#include "Application.h"

using namespace MGE;

SpriteRendererComponent::SpriteRendererComponent(std::string name) : _texture(), _sprite(_texture)
{
    _name = name;
}

SpriteRendererComponent::SpriteRendererComponent(std::string name, sf::Texture texture) : _texture(texture), _sprite(_texture)
{
    _name = name;
}

void SpriteRendererComponent::Update(float deltaTime)
{
}

void SpriteRendererComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // A priori ça fonctionne avec le transform du sprite
    // sf::Vector2u size = _texture.getSize();
    // states.transform.translate(-(size.x / 2.0f), -(size.y / 2.0f));
    target.draw(_sprite, states);
}

const sf::Sprite& SpriteRendererComponent::getSprite()
{
    return _sprite;
}

const sf::Texture& SpriteRendererComponent::getTexture()
{
    return _texture;
}

// Not confident that won't cause leaks...
void SpriteRendererComponent::setTexture(sf::Texture texture)
{
    _texture = texture;
    _sprite.setTexture(_texture, true);
}

void MGE::SpriteRendererComponent::loadAndSetTexture(std::string path)
{
    sf::Texture newTexture;
    if (!newTexture.loadFromFile(path))
    {
        std::cerr << "Could not load texture" << std::endl;
    }
    else {
        setTexture(newTexture);
    }
}

void MGE::SpriteRendererComponent::BeginCollision(Collision collision)
{
    auto bodyA = collision.getOtherComp();
    auto bodyB = collision.getOtherComp();
    std::cout << std::format("Collision Begin: self: {}, bodyA: ({}, {}), bodyB: ({}, {}) \n", 
        _name, bodyA->GetPosition().x, bodyA->GetPosition().y, bodyB->GetPosition().x, bodyB->GetPosition().y);
}

void MGE::SpriteRendererComponent::EndCollision(Collision collision)
{
    auto bodyA = collision.getOtherComp();
    auto bodyB = collision.getOtherComp();
    std::cout << std::format("Collision End: self: {}, bodyA: ({}, {}), bodyB: ({}, {}) \n",
        _name, bodyA->GetPosition().x, bodyA->GetPosition().y, bodyB->GetPosition().x, bodyB->GetPosition().y);
}

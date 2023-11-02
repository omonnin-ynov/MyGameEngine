#include "SpriteRendererComponent.h"
#include <iostream>
#include "ResourceManager.h"
#include "Application.h"

using namespace MGE;

SpriteRendererComponent::SpriteRendererComponent(std::string name) : _texture(), _sprite(_texture)
{
}

SpriteRendererComponent::SpriteRendererComponent(std::string name, sf::Texture texture) : _texture(texture), _sprite(_texture)
{
}

void SpriteRendererComponent::Update(float deltaTime)
{
}

void SpriteRendererComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // A priori �a fonctionne avec le transform du sprite
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

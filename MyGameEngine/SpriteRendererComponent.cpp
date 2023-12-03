#include "SpriteRendererComponent.h"
#include <format> 
#include <functional>
#include <iostream>
#include "ResourceManager.h"
#include "Application.h"

using namespace MGE;

SpriteRendererComponent::SpriteRendererComponent(std::string name) : _sprite(_texture), _texture()
{
    _name = name;
}

SpriteRendererComponent::SpriteRendererComponent(std::string name, sf::Texture texture) : _sprite(_texture), _texture(texture)
{
    _name = name;
}

void SpriteRendererComponent::Awake()
{
}

void SpriteRendererComponent::Start()
{
}

void SpriteRendererComponent::LateUpdate(float deltaTime)
{
}

void SpriteRendererComponent::Update(float deltaTime)
{
}

void SpriteRendererComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
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
        std::cerr << "Could not load texture in spriteRendererComponent : " << path << "\n";
    }
    else {
        setTexture(newTexture);
    }
}

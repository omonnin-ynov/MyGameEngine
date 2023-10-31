#pragma once
#include "AComponent.h"

// TODO sprite colors
namespace MGE {
    class SpriteRendererComponent :
        public AComponent, public sf::Drawable
    {
    protected:
        sf::Sprite _sprite;
        sf::Texture _texture;

    public:
        SpriteRendererComponent(std::string name);
        SpriteRendererComponent(std::string name, sf::Texture texture);

        virtual void Update(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        const sf::Sprite& getSprite();

        const sf::Texture& getTexture();
        void setTexture(sf::Texture texture);
        void loadAndSetTexture(std::string name);
    };

}

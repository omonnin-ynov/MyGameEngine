#pragma once
#include "AComponent.h"
#include "ICollidable.h"

namespace MGE {
    class SpriteRendererComponent :
        public AComponent, public sf::Drawable, public ICollidable
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
        void loadAndSetTexture(std::string path);

        // Inherited via ICollidable
        virtual void BeginCollision(Collision collision) override;
        virtual void EndCollision(Collision collision) override;
    };

}


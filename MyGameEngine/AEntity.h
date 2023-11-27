#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "AComponent.h"

namespace MGE {
    class AEntity : public sf::Transformable, public sf::Drawable {
    protected:
        uint64_t _ID;
        std::string _name;
        std::vector<AComponent*> _components;

    public:
        AEntity();
        AEntity(std::string name);
        AEntity(std::string name, float x, float y);

        virtual void Awake();
        virtual void Start();
        virtual void Update(float deltaTime);
        virtual void LateUpdate(float deltaTime);

        std::vector<AComponent*>* getComponents();
        void attachComponent(AComponent* component);
        void detachComponent(AComponent* component);

        uint64_t getID();
        std::string getName() const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        std::string E();
    };
}


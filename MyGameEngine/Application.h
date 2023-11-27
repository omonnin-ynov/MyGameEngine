#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ranges>

#include "PhysicsSystem.h"
#include "AEntity.h"
#include "CameraComponent.h"

namespace MGE {
    class Application {
    protected:
        
        uint64_t _IDCounter;
        static Application* _instance;
        // Should be public?
        PhysicsSystem _physics;

        std::map<uint64_t, AEntity*> _entities;
        std::map<uint64_t, AComponent*> _components;
        std::map<uint64_t, uint64_t> _compToEntityLink;
        std::vector<uint64_t> _toBeDeleted;

        sf::RenderWindow* _window;
        bool _shouldExit;
        CameraComponent* _activeCameraComponent;
        Application();

    public:

        static Application* getInstance();

        void start();

        void initalizeWindow(int x, int y);

        void update(float deltaTime);

        void handleInput();

        uint64_t GenerateID();

        std::map<uint64_t, AEntity*>* getEntities();
        std::map<uint64_t, AComponent*>* getComponents();

        PhysicsSystem& getPhysics();
        b2World* getWorld();

        sf::RenderWindow* getWindow();

        MGE::CameraComponent* getActiveCamera();

        void setActiveCamera(CameraComponent* cameraComp);

        AEntity* getEntityFromID(uint64_t ID);

        AComponent* getComponentFromID(uint64_t ID);

        AEntity* getParentEntity(AComponent* comp);

        void registerEntity(AEntity* entity);
        void registerEntityAndAttachedComponents(AEntity* entity);
        void registerComponent(AComponent* comp, AEntity* parent);
        void markForDeletion(uint64_t ID);

        void createSpriteAndPhysicsComponents(AEntity* parent, sf::Texture texture, b2BodyType bodyType, bool isSensor);

        template <std::derived_from<AEntity> T>
        T* createEntity(std::string name)
        {
            T* newEntity = new T(name);
            _entities[newEntity->getID()] = newEntity;
            return newEntity;
        }

        void destroyEntity(AEntity* entity);        

        /// \brief adds all components of type T to result vector passed in param
        /// \tparam T the type to find
        /// \param result your vector + all registered components of type T
        template <std::derived_from<AComponent> T>
        void getComponentsOfType(std::vector<T*>* result)
        {
            for (auto comp : _components | std::views::values)
            {
                if (T* testComp = dynamic_cast<T*>(comp))
                {
                    result->push_back(testComp);
                }
            }
        }

        template <std::derived_from<AComponent> T>
        T* createComponent(std::string name)
        {
            T* newComp = new T(name);
            _components[newComp->getID()] = newComp;
            return newComp;
        }

        template <std::derived_from<AComponent> T>
        T* createComponentAndAttach(std::string name, MGE::AEntity* entity)
        {
            T* newComp = new T(name);
            _components[newComp->getID()] = newComp;
            _compToEntityLink[newComp->getID()] = entity->getID();
            entity->attachComponent(newComp);
            return newComp;
        }

        void destroyComponent(AComponent* comp);
    };
}

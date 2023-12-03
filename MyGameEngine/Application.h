#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <ranges>
#include <random>
#include "PhysicsSystem.h"
#include "AEntity.h"
#include "CameraComponent.h"
#include "LuaSystem.h"

namespace MGE
{
	class RigidBodyComponent;

	class Application
	{
	protected:
		uint64_t _IDCounter;
		// std::rand c'est de la merde
		std::mt19937 _rng;

		static Application* _instance;
		PhysicsSystem _physics;
		LuaSystem _luaSystem;

		// TODO if there's time, make sure the first 3 maps can't be modified by unintended means
		std::map<uint64_t, AEntity*> _entities;
		std::map<uint64_t, AComponent*> _components;
		std::map<uint64_t, uint64_t> _compToEntityLink;
		// I'm ok with adding an extra map to keep track of, bc only the RigidBodyComponent will ever modify it
		// and it makes collisions much more efficient
		std::map<b2Body*, RigidBodyComponent*> _b2BodyToComp;
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
		std::map<b2Body*, RigidBodyComponent*>* getb2BodyToComp();

		PhysicsSystem& getPhysics();
		b2World* getWorld();
		LuaSystem* getLua();

		sf::RenderWindow* getWindow() const;

		CameraComponent* getActiveCamera() const;

		void setActiveCamera(CameraComponent* cameraComp);

		AEntity* getEntityFromID(uint64_t ID);

		AComponent* getComponentFromID(uint64_t ID);

		AEntity* getParentEntity(AComponent* comp);

		int getRand();
		void registerEntity(AEntity* entity);
		void registerEntityAndAttachedComponents(AEntity* entity);
		void registerComponent(AComponent* comp, AEntity* parent);
		void markForDeletion(uint64_t ID);

		void createSpriteAndPhysicsComponents(AEntity* parent, sf::Texture& texture, b2BodyType bodyType, bool isSensor,
		                                      uint16 collisionGroup, uint16 collisionMask);

		template <typename T>
		std::enable_if_t<std::is_base_of_v<AEntity*, T*>, void> createEntity(std::string name)
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
		T* createComponentAndAttach(std::string name, AEntity* entity)
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

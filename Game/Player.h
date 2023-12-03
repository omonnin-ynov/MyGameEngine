#pragma once
#include "IDamageable.h"
#include "MyGameEngine/AEntity.h"
#include "MyGameEngine/ICollidable.h"

namespace ILM
{
	class Player :
		public MGE::AEntity,
		public MGE::ICollidable,
		public IDamageable
	{
	public:
		Player(std::string name, float x, float y, float hp, float damage);

		// From AEntity
		void Awake() override;
		void Start() override;

		// From ICollidable
		void BeginCollision(MGE::Collision collision) override;
		void EndCollision(MGE::Collision collision) override;

		// From IDamageable
		float takeDamage(MGE::AEntity* parent, float damage) override;
	};
}

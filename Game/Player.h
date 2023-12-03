#pragma once
#include "IDamageable.h"
#include "MyGameEngine/AEntity.h"

namespace ILM
{
	class Player :
		public MGE::AEntity,
		public IDamageable
	{
	public:
		Player(std::string name, float x, float y, float hp, float damage);

		void Awake() override;
		void Start() override;

		float takeDamage(MGE::AEntity* parent, float damage) override;
	};
}

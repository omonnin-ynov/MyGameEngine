#include "Player.h"

ILM::Player::Player(std::string name, float x, float y, float hp, float damage)
	: AEntity(name, x, y),
	IDamageable(hp, damage)
{
}

void ILM::Player::Awake()
{
}

void ILM::Player::Start()
{
}

void ILM::Player::BeginCollision(MGE::Collision collision)
{
}

void ILM::Player::EndCollision(MGE::Collision collision)
{
}

float ILM::Player::takeDamage(MGE::AEntity* parent, float damage)
{
	_hp -= damage;
	return damage;
}

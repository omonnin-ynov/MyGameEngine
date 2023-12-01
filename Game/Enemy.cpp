#include "Enemy.h"


ILM::Enemy::Enemy(std::string name) : MGE::AEntity(name)
{
}

ILM::Enemy::Enemy(std::string name, float speed, float hp, float damage, AEntity* target)
    : MGE::AEntity(std::move(name)),
    _speed(speed),
    _hp(hp),
    _damage(damage),
    _target(target)
{
}

void ILM::Enemy::Update(float deltaTime)
{
    AEntity::Update(deltaTime);

    // get enemy direction
    sf::Vector2f direction = _target->getPosition() - getPosition();
    //normalize direction vector
    float directionLen = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    this->move((direction / directionLen) * _speed * deltaTime);
}

float ILM::Enemy::getSpeed() const
{
    return _speed;
}

void ILM::Enemy::setSpeed(float speed)
{
    _speed = speed;
}

float ILM::Enemy::getHp() const
{
    return _hp;
}

void ILM::Enemy::removeHP(float hp)
{
    _hp -= hp;
}

void ILM::Enemy::setHp(float hp)
{
    _hp = hp;
}

MGE::AEntity* ILM::Enemy::getTarget() const
{
    return _target;
}

void ILM::Enemy::setTarget(AEntity* target)
{
    _target = target;
}


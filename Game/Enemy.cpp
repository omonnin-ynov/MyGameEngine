#include "Enemy.h"
#include "MyGameEngine/Application.h"

ILM::Enemy::Enemy(std::string name) : MGE::AEntity(name), IDamageable(0, 0), _speed(0), _target()
{
}

ILM::Enemy::Enemy(std::string name, float speed, float hp, float damage, AEntity* target)
    : MGE::AEntity(std::move(name)),
    IDamageable(hp, damage),
    _speed(speed),
    _target(target)
{
}

void ILM::Enemy::Awake()
{
}

void ILM::Enemy::Start()
{
}

void ILM::Enemy::Update(float deltaTime)
{
    AEntity::Update(deltaTime);

    if (_target)
    {
        // get enemy direction
        sf::Vector2f direction = _target->getPosition() - getPosition();
        //normalize direction vector
        float directionLen = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        this->move((direction / directionLen) * _speed * deltaTime);
    }
}

float ILM::Enemy::getSpeed() const
{
    return _speed;
}

void ILM::Enemy::setSpeed(float speed)
{
    _speed = speed;
}

float ILM::Enemy::takeDamage(MGE::AEntity* parent, float damage)
{
    _hp -= damage;
    if (_hp <= 0)
    {
        MGE::Application::getInstance()->markForDeletion(this->getID());
        return damage + _hp;
    }
    return damage;
}

MGE::AEntity* ILM::Enemy::getTarget() const
{
    return _target;
}

void ILM::Enemy::setTarget(AEntity* target)
{
    _target = target;
}

void ILM::Enemy::BeginCollision(MGE::Collision collision)
{
    if (auto damageableEntity = dynamic_cast<IDamageable*>(collision.getOtherParent()))
    {
        float damageDealt = damageableEntity->takeDamage(this, _damage);
    }
}

void ILM::Enemy::EndCollision(MGE::Collision collision)
{
}


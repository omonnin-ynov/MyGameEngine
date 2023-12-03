#include "Projectile.h"
#include "MyGameEngine/Application.h"

float ILM::Projectile::getSpeed() const
{
    return _speed;
}

void ILM::Projectile::setSpeed(float speed)
{
    _speed = speed;
}

float ILM::Projectile::getElapsedTime()
{
    return timer.getElapsedTime().asSeconds();
}

void ILM::Projectile::resetTimer()
{
    timer.restart();
}

void ILM::Projectile::BeginCollision(MGE::Collision collision)
{
    auto damageableEntity = dynamic_cast<IDamageable*>(collision.getOtherParent());
    if (_hp > 0 && damageableEntity)
    {
        float damageDealt = damageableEntity->takeDamage(this, _damage);
    }
}

void ILM::Projectile::EndCollision(MGE::Collision collision)
{
}

float ILM::Projectile::takeDamage(MGE::AEntity* parent, float damage)
{
    _hp -= 1.0f;
    if (_hp <= 0)
    {
        MGE::Application::getInstance()->markForDeletion(this->getID());
    }
    // Projectile damage dealt is a special case and shouldn't be used for calculations
    return 0.0f;
}

ILM::Projectile::Projectile(std::string name) : AEntity(name), IDamageable(0, 0), _speed(200.0f), _areaMod(1), _duration(2.0f)
{
    timer.restart();
}

ILM::Projectile::Projectile(const std::string& name, float speed, float damage, float areaMod, float duration, float hp)
    : AEntity(name),
	IDamageable(hp, damage),
    _speed(speed),
    _areaMod(areaMod),
    _duration(duration)
{
    timer.restart();
}

void ILM::Projectile::Awake()
{
}

void ILM::Projectile::Start()
{
}

void ILM::Projectile::Update(float deltaTime)
{
    MGE::AEntity::Update(deltaTime);
    if (timer.getElapsedTime().asSeconds() > _duration)
    {
        MGE::Application::getInstance()->markForDeletion(this->getID());
    }
}

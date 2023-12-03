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

ILM::Projectile::Projectile(const std::string& name, float speed, float damage, float areaMod, float duration, int hp)
    : AEntity(name),
	IDamageable(hp, damage),
    _speed(speed),
    _areaMod(areaMod),
    _duration(duration)
{
    timer.restart();
}

void ILM::Projectile::Update(float deltaTime)
{
    MGE::AEntity::Update(deltaTime);
    if (timer.getElapsedTime().asSeconds() > _duration)
    {
        MGE::Application::getInstance()->markForDeletion(this->getID());
    }
    // rotate direction vector (0, 1) by the rotation of the projectile
    //float rotation = getRotation() * (b2_pi / 180);
    //sf::Vector2f direction{ -1 * std::sin(rotation), std::cos(rotation) };
    //direction *= _speed * - 1;
    //this->move(direction * deltaTime);
    //AEntity::Update(deltaTime);
}

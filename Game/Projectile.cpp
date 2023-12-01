#include "Projectile.h"
#include <iostream>
#include "box2d/b2_math.h"
#include "MyGameEngine/Application.h"
#include "MyGameEngine/BoxCollider.h"
#include "MyGameEngine/RigidBodyComponent.h"
#include "MyGameEngine/SpriteRendererComponent.h"

float ILM::Projectile::getDamage() const
{
    return _damage;
}

void ILM::Projectile::setDamage(float damage)
{
    _damage = damage;
}

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

ILM::Projectile::Projectile(std::string name) : AEntity(name), _speed(200.0f), _damage(1.0f), _areaMod(1), _duration(2.0f)
{
    timer.restart();
}

ILM::Projectile::Projectile(const std::string& name, float speed, float damage, float areaMod, float duration)
    : AEntity(name),
    _speed(speed),
    _damage(damage),
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

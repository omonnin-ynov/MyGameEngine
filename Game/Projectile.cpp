#include "Projectile.h"
#include <iostream>
#include "box2d/b2_math.h"
#include "MyGameEngine/SpriteRendererComponent.h"

ILM::Projectile* ILM::Projectile::copy(float speedMod, float damageMod, float areaMod, float durationMod)
{
    // TODO AREAAAA
    auto newProj = new Projectile(this->_name, this->_speed * speedMod, this->_damage * damageMod, areaMod, this->_duration * durationMod, this->_baseSpawnRate);
    newProj->setRotation(std::rand() % 361);
    auto sprite = new MGE::SpriteRendererComponent("test");
    std::cout << "making sprite";
    sprite->loadAndSetTexture("res/fireball.png");
    newProj->attachComponent(sprite);
    return newProj;
}

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

float ILM::Projectile::getBaseSpawnRate() const
{
    return _baseSpawnRate;
}

void ILM::Projectile::setBaseSpawnRate(float baseSpawnRate)
{
    _baseSpawnRate = baseSpawnRate;
}

float ILM::Projectile::getElapsedTime()
{
    return timer.getElapsedTime().asSeconds();
}

void ILM::Projectile::resetTimer()
{
    timer.restart();
}

ILM::Projectile::Projectile(std::string name) : AEntity(name), _speed(200.0f), _damage(1.0f), _areaMod(1), _duration(), _baseSpawnRate(1.0f)
{
}

ILM::Projectile::Projectile(const std::string& name, float speed, float damage, float areaMod, float duration, float baseSpawnRate)
    : AEntity(name),
    _speed(speed),
    _damage(damage),
    _areaMod(areaMod),
    _duration(duration),
    _baseSpawnRate(baseSpawnRate)
{
}

void ILM::Projectile::Update(float deltaTime)
{
    if (timer.getElapsedTime().asSeconds() < _duration)
    {
        
    }
    // rotate direction vector (0, 1) by the rotation of the projectile
    float rotation = getRotation() * (b2_pi / 180);
    sf::Vector2f direction{ -1 * std::sin(rotation), std::cos(rotation) };
    direction *= _speed * - 1;
    this->move(direction * deltaTime);
    AEntity::Update(deltaTime);
}

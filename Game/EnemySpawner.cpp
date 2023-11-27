#include "EnemySpawner.h"

#include <iostream>

#include "Enemy.h"
#include "MyGameEngine/Application.h"

ILM::EnemySpawner::EnemySpawner(std::string name) : _spawnRateMod(1), _speedMod(1), _damageMod(1), _hpMod()
{
}

ILM::EnemySpawner::EnemySpawner(std::string name, float spawnRateMod, float speedMod, float damageMod, float hpMod)
    : AComponent(std::move(name)),
    _spawnRateMod(spawnRateMod),
    _speedMod(speedMod),
    _damageMod(damageMod),
    _hpMod(hpMod)
{
}

float ILM::EnemySpawner::getSpawnRateMod() const
{
    return _spawnRateMod;
}

void ILM::EnemySpawner::setSpawnRateMod(float spawnRateMod)
{
    _spawnRateMod = spawnRateMod;
}

float ILM::EnemySpawner::getSpeedMod() const
{
    return _speedMod;
}

void ILM::EnemySpawner::setSpeedMod(float speedMod)
{
    _speedMod = speedMod;
}

float ILM::EnemySpawner::getDamageMod() const
{
    return _damageMod;
}

void ILM::EnemySpawner::setDamageMod(float damageMod)
{
    _damageMod = damageMod;
}

float ILM::EnemySpawner::getHpMod() const
{
    return _hpMod;
}

void ILM::EnemySpawner::setHpMod(float hpMod)
{
    _hpMod = hpMod;
}

void ILM::EnemySpawner::Update(float deltaTime)
{
    MGE::Application* app = MGE::Application::getInstance();

    for (auto& [name, enemyInfo] : _enemies)
    {
        if (enemyInfo._clock.getElapsedTime().asSeconds() > enemyInfo._baseSpawnRate * _spawnRateMod)
        {
            enemyInfo._clock.restart();

            auto newEnemy = new Enemy(name, enemyInfo._speed * _speedMod, enemyInfo._hp * _hpMod, enemyInfo._damage * _damageMod, app->getParentEntity(this));
            //TODO w.r.t. screen position
            newEnemy->setPosition(app->getParentEntity(this)->getPosition());

            app->createSpriteAndPhysicsComponents(newEnemy, enemyInfo._texture, b2_staticBody, true);
            // thankfully, adding elements to std::map does not invalidate iterators (from the Update implicit for loop)
            app->registerEntityAndAttachedComponents(newEnemy);
        }
    }
}

void ILM::EnemySpawner::addEnemy(std::string enemyName, std::string enemyType, std::string texturePath, float speed, float HP, float damage,
                                 float baseSpawnRate, float scale)
{
    if (!_enemies.contains(enemyName))
    {
        sf::Texture texture;
        if (!texture.loadFromFile(texturePath))
        {
            std::cout << "warning: Could not load texture in enemySpawner::addEnemy : " << texturePath << "\n";
            return;
        }
        _enemies[enemyName] = EnemyInfo{ enemyType, texture, speed, HP, damage, baseSpawnRate, scale };
    }
    else std::cout << "warning: enemy with same name already exists in enemy spawner\n";
}

void ILM::EnemySpawner::clearEnemies()
{
    _enemies.clear();
}

void ILM::EnemySpawner::removeEnemy(std::string name)
{
    int removed = _enemies.erase(name);
    if (!removed)
    {
        std::cout << "warning: attempt to remove nonexistent enemy from enemy spawner\n";
    }
}

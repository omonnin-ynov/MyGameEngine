#include "EnemySpawner.h"

#include <iostream>
#include "Enemy.h"
#include "MyGameEngine/Application.h"

sf::Vector2f ILM::EnemySpawner::sampleRandomPointOnRectPerimeter(sf::Vector2f& rectangle)
{

    // Unfold the rectangle in a line starting from the top-left corner
    float rectangleLength = rectangle.x * 2 + rectangle.y * 2;
    // pick a random point on the line
    // why is there no random float function
    int pointOnRectangle = MGE::Application::getInstance()->getInstance()->getRand() % static_cast<int>(rectangleLength);

    // get back the position on the rectangle
    if (pointOnRectangle < rectangle.x)
    {
        return { static_cast<float>(pointOnRectangle), 0 };
    }
    pointOnRectangle -= rectangle.x;
    if (pointOnRectangle < rectangle.y)
    {
        return { rectangle.x, static_cast<float>(pointOnRectangle) };
    }
    pointOnRectangle -= rectangle.y;
    if (pointOnRectangle < rectangle.x)
    {
        return { static_cast<float>(pointOnRectangle), rectangle.y };
    }
    else return {0, static_cast<float>(pointOnRectangle) - rectangle.x};
}

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

            // Get player position and viewport size to spawn enemies slightly outside the viewport
            sf::Vector2f spawnRectangle = app->getActiveCamera()->getCameraViewportSize() * 1.1f;
            sf::Vector2f spawnOffset = sampleRandomPointOnRectPerimeter(spawnRectangle);
            spawnOffset = { spawnOffset.x - (spawnRectangle.x / 2.0f), spawnOffset.y - (spawnRectangle.y / 2.0f)};
            sf::Vector2f enemyPosition = app->getParentEntity(this)->getPosition() + spawnOffset;
            newEnemy->setPosition(enemyPosition);

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

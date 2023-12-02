#include "TimedProjectileSpawner.h"
#include <format>

#include "LuaProjectileMovement.h"
#include "MyGameEngine/Application.h"
#include "Projectile.h"
#include "MyGameEngine/BoxCollider.h"
#include "MyGameEngine/ResourceManager.h"
#include "MyGameEngine/RigidBodyComponent.h"
#include "MyGameEngine/SpriteRendererComponent.h"

ILM::TimedProjectileSpawner::TimedProjectileSpawner(std::string name) : _spawnRateMod(1.0f), _speedMod(1.0f), _damageMod(1.0f), _areaMod(1.0f), _amountMod(1), _durationMod(1.0f)
{
}

float ILM::TimedProjectileSpawner::getSpawnRateMod() const
{
    return _spawnRateMod;
}

void ILM::TimedProjectileSpawner::setSpawnRateMod(float spawnRateMod)
{
    _spawnRateMod = spawnRateMod;
}

float ILM::TimedProjectileSpawner::getSpeedMod() const
{
    return _speedMod;
}

void ILM::TimedProjectileSpawner::setSpeedMod(float speedMod)
{
    _speedMod = speedMod;
}

float ILM::TimedProjectileSpawner::getDamageMod() const
{
    return _damageMod;
}

void ILM::TimedProjectileSpawner::setDamageMod(float damageMod)
{
    _damageMod = damageMod;
}

float ILM::TimedProjectileSpawner::getAreaMod() const
{
    return _areaMod;
}

void ILM::TimedProjectileSpawner::setAreaMod(float areaMod)
{
    _areaMod = areaMod;
}

float ILM::TimedProjectileSpawner::getDurationMod() const
{
    return _durationMod;
}

void ILM::TimedProjectileSpawner::setDurationMod(float durationMod)
{
    _durationMod = durationMod;
}

int ILM::TimedProjectileSpawner::getAmountMod() const
{
    return _amountMod;
}

void ILM::TimedProjectileSpawner::setAmountMod(int amountMod)
{
    _amountMod = amountMod;
}

ILM::TimedProjectileSpawner::TimedProjectileSpawner(std::string name, float spawnRateMod, float speedMod, float damageMod, float areaMod,
                                                    float durationMod, int amountMod)
    : AComponent(std::move(name)),
    _spawnRateMod(spawnRateMod),
    _speedMod(speedMod),
    _damageMod(damageMod),
    _areaMod(areaMod),
    _durationMod(durationMod),
    _amountMod(amountMod)
{
}

void ILM::TimedProjectileSpawner::Update(float deltaTime)
{
    MGE::Application* app =  MGE::Application::getInstance();

    // attempt projectile spawn
    for (auto& [name, info] : _projectiles)
    {
        if (info._clock.getElapsedTime().asSeconds() > info._baseSpawnRate * _spawnRateMod)
        {
            info._clock.restart();

            // TODO different projectile types with LUA scripts
            ILM::Projectile* newProj;
            /*switch (info._projectileType)
            {
            case "projectile":*/
                newProj = new Projectile(name, info._speed * _speedMod, info._damage * _damageMod, _areaMod, info._duration *_durationMod, info._hp);
                newProj->setPosition(app->getParentEntity(this)->getPosition());
                newProj->setRotation(std::rand() % 361);
                newProj->setScale(info._scale, info._scale);
            //}
            if (!newProj)
            {
                std::cout << std::format("warning: could not instantiate projectile entity name : {}, type : {} in projectileSpawner::Update\n", name, info._projectileType);
                continue;
            }

            app->createSpriteAndPhysicsComponents(newProj, info._texture, b2_dynamicBody, true, 0x0002, 0x0004);

            auto luaScriptComp = new ILM::LuaProjectileMovement("LuaProjectileMovement");
            newProj->attachComponent(luaScriptComp);

            // thankfully, adding elements to std::map does not invalidate iterators (from the Update implicit for loop)
            app->registerEntityAndAttachedComponents(newProj);
        }
    }
}

void ILM::TimedProjectileSpawner::addProjectile(std::string projectileName, std::string projectileType,
                                                std::string texturePath, float speed, float damage, float duration, int hp, float scale, float baseSpawnRate)
{
    if (!_projectiles.contains(projectileName))
    {
        sf::Texture texture;
        if (!texture.loadFromFile(texturePath))
        {
            std::cout << "warning: Could not load texture in timedProjectileSpawner::addProjectile : " << texturePath << "\n";
            return;
        }
        _projectiles[projectileName] = ProjectileInfo{ projectileType, texture, speed, damage, duration, hp, scale, baseSpawnRate };
    }
    else std::cout << "warning: projectile with same name already exists in projectile spawner\n";
}

void ILM::TimedProjectileSpawner::clearProjectiles()
{
    _projectiles.clear();
}

void ILM::TimedProjectileSpawner::removeProjectile(std::string projectileName)
{
    int removed = _projectiles.erase(projectileName);
    if (!removed)
    {
        std::cout << "warning: attempt to remove nonexistent projectile from projectile spawner\n";
    }
}

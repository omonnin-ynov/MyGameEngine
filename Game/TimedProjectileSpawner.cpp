#include "TimedProjectileSpawner.h"
#include "MyGameEngine/Application.h"
#include "Projectile.h"

ILM::TimedProjectileSpawner::TimedProjectileSpawner(std::string name) : _spawnRateMod(1.0f), _speedMod(1.0f), _damageMod(1.0f), _areaMod(1.0f), _amountMod(1)
{
}

void ILM::TimedProjectileSpawner::Update(float deltaTime)
{
    MGE::AComponent::Update(deltaTime);
    auto app = MGE::Application::getInstance();
    for (auto projectile: _projectiles)
    {
        if (projectile->getBaseSpawnRate() * _spawnRateMod < projectile->getElapsedTime())
        {
            for (int i = 0; i < _amountMod; i++)
            {
                auto newProj = projectile->copy(_speedMod, _damageMod, _areaMod, _durationMod);
                app->registerEntityAndAttachedComponents(newProj);
            }
            projectile->resetTimer();
        }
    }
}

void ILM::TimedProjectileSpawner::addProjectile(Projectile* projectile)
{
    _projectiles.push_back(projectile);
}

void ILM::TimedProjectileSpawner::clearProjectiles()
{
    _projectiles.clear();
}

void ILM::TimedProjectileSpawner::removeProjectile(Projectile* projectile)
{
    
}

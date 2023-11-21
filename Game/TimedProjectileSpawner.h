#pragma once
#include "MyGameEngine/AComponent.h"

namespace ILM
{
    class Projectile;
    class TimedProjectileSpawner :
        public MGE::AComponent
    {
    protected:
        float _spawnRateMod;
        float _speedMod;
        float _damageMod;
        float _areaMod;
        float _durationMod;
        int _amountMod;
        std::vector<Projectile*> _projectiles;

    public:
        TimedProjectileSpawner(std::string name);
        ~TimedProjectileSpawner();

        virtual void Update(float deltaTime) override;

        void addProjectile(Projectile* projectile);
        void clearProjectiles();
        void removeProjectile(Projectile* projectile);
    };
}

#pragma once
#include "MyGameEngine/AEntity.h"

namespace ILM
{
    class Projectile :
        public MGE::AEntity
    {
    protected:
        float _speed;
        float _damage;
        float _areaMod;
        float _duration;
        float _baseSpawnRate;
        // Self-destruct timer, used as spawn timer if projectile registered in TimedProjectileSpawner
        sf::Clock timer;

    public:
        Projectile(std::string name);

        Projectile(const std::string& name, float speed, float damage, float areaMod, float duration, float baseSpawnRate);

        void Update(float deltaTime) override;

        Projectile* copy(float speedMod, float damageMod, float areaMod, float durationMod);

        float getDamage() const;
        void setDamage(float damage);
        float getSpeed() const;
        void setSpeed(float speed);
        float getBaseSpawnRate() const;
        void setBaseSpawnRate(float baseSpawnRate);
        float getElapsedTime();
        void resetTimer();
    };
}

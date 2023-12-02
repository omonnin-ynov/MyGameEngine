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
        int _hp;
        // Self-destruct timer, used as spawn timer if projectile registered in TimedProjectileSpawner
        sf::Clock timer;

    public:
        Projectile(std::string name);

        Projectile(const std::string& name, float speed, float damage, float areaMod, float duration, int hp);

        void Update(float deltaTime) override;

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

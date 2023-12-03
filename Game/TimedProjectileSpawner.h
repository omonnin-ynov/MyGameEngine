#pragma once
#include "MyGameEngine/AComponent.h"

namespace ILM
{
    class Projectile;
    class TimedProjectileSpawner :
        public MGE::AComponent
    {
        struct ProjectileInfo
        {
            std::string _projectileType;
            sf::Texture _texture;
            float _speed;
            float _damage;
            float _duration;
            float _hp;
            float _scale;
            float _baseSpawnRate;
            sf::Clock _clock;
        };

    protected:
        float _spawnRateMod;
        float _speedMod;
        float _damageMod;
        float _areaMod;
        float _durationMod;
        int _amountMod;
        std::map<std::string, ProjectileInfo> _projectiles;

    public:
        TimedProjectileSpawner(std::string name);

        TimedProjectileSpawner(std::string name, float spawnRateMod, float speedMod, float damageMod, float areaMod,
            float durationMod, int amountMod);

        float getSpawnRateMod() const;
        void setSpawnRateMod(float spawnRateMod);
        float getSpeedMod() const;
        void setSpeedMod(float speedMod);
        float getDamageMod() const;
        void setDamageMod(float damageMod);
        float getAreaMod() const;
        void setAreaMod(float areaMod);
        float getDurationMod() const;
        void setDurationMod(float durationMod);
        int getAmountMod() const;
        void setAmountMod(int amountMod);

        void Awake() override;
        void Start() override;
        void Update(float deltaTime) override;
        void LateUpdate(float deltaTime) override;

        void addProjectile(std::string projectileName, std::string projectileType, std::string texturePath, float speed, float damage, float
                           duration, float hp, float scale, float baseSpawnRate);
        void clearProjectiles();
        void removeProjectile(std::string projectileName);
    };
}

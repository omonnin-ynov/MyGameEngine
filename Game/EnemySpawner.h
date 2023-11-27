#pragma once
#include "MyGameEngine/AComponent.h"

namespace ILM
{
    class EnemySpawner :
        public MGE::AComponent
    {
        struct EnemyInfo
        {
            std::string _enemyType;
            sf::Texture _texture;
            float _speed;
            float _hp;
            float _damage;
            float _baseSpawnRate;
            float _scale;
            sf::Clock _clock;
        };
    protected:
        float _spawnRateMod;
        float _speedMod;
        float _damageMod;
        float _hpMod;
        std::map<std::string, EnemyInfo> _enemies;

    public:
        EnemySpawner(std::string name);
        EnemySpawner(std::string name, float spawnRateMod, float speedMod, float damageMod, float hpMod);

        float getSpawnRateMod() const;
        void setSpawnRateMod(float spawnRateMod);
        float getSpeedMod() const;
        void setSpeedMod(float speedMod);
        float getDamageMod() const;
        void setDamageMod(float damageMod);
        float getHpMod() const;
        void setHpMod(float hpMod);

        void Update(float deltaTime) override;

        void addEnemy(std::string enemyName, std::string enemyType, std::string texturePath, float speed, float HP, float damage, float baseSpawnRate, float scale);
        void clearEnemies();
        void removeEnemy(std::string name);
    };
}

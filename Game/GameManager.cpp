#include "GameManager.h"
#include "EnemySpawner.h"
#include "Player.h"
#include "TimedProjectileSpawner.h"
#include "MyGameEngine/Application.h"

MGE::AEntity* ILM::ILMResourceManager::instantiatePlayer(std::string name)
{
    auto app = MGE::Application::getInstance();
    MGE::AEntity* playerEntity{};
    for (YAML::Node player : _config["player"])
    {
        if (player["name"].as<std::string>() == name)
        {
            float playerHP = player["hp"].as<float>();
            playerEntity = new Player(player["name"].as<std::string>(), 0, 0, playerHP, 0);
            playerEntity->scale(player["scale"].as<float>(), player["scale"].as<float>());
            // Get player Sprite
            auto spriteNode = player["sprite"];
            sf::Texture playerTexture;
            playerTexture.loadFromFile(getPathFromName(spriteNode["textureName"].as<std::string>()));
            app->createSpriteAndPhysicsComponents(playerEntity, playerTexture, b2_dynamicBody, true, 0x0001, 0x0004);

            auto projectileSpawnerNode = player["projectileSpawner"];
            auto PSName = projectileSpawnerNode["name"].as<std::string>();
            float PSSpawnRateMod = projectileSpawnerNode["spawnRateMod"].as<float>();
            float PSSpeedMod = projectileSpawnerNode["speedMod"].as<float>();
            float PSDamageMod = projectileSpawnerNode["damageMod"].as<float>();
            float PSAreaMod = projectileSpawnerNode["areaMod"].as<float>();
            float PSDurationMod = projectileSpawnerNode["durationMod"].as<float>();
            int PSAmountMod = projectileSpawnerNode["amountMod"].as<int>();

            auto projectileSpawner = new ILM::TimedProjectileSpawner(PSName, PSSpawnRateMod, PSSpeedMod, PSDamageMod, PSAreaMod, PSDurationMod, PSAmountMod);

            // store pre-instantiation projectile definitions

            for (YAML::Node projectileInfo : projectileSpawnerNode["playerProjectiles"])
            {
                projectileSpawner->addProjectile(projectileInfo["name"].as<std::string>(),
                    projectileInfo["type"].as<std::string>(),
                    getPathFromName(projectileInfo["textureName"].as<std::string>()),
                    projectileInfo["speed"].as<float>(),
                    projectileInfo["damage"].as<float>(),
                    projectileInfo["duration"].as<float>(),
                    projectileInfo["hp"].as<float>(),
                    projectileInfo["scale"].as<float>(),
                    projectileInfo["baseSpawnRate"].as<float>());
            }

            playerEntity->attachComponent(projectileSpawner);
        }
    }

    YAML::Node enemySpawnerNode = _config["enemySpawner"];
    auto enemyName = enemySpawnerNode["name"].as<std::string>();
    float enemySpawnRateMod = enemySpawnerNode["spawnRateMod"].as<float>();
    float enemySpeedMod = enemySpawnerNode["speedMod"].as<float>();
    float enemyDamageMod = enemySpawnerNode["damageMod"].as<float>();
    float enemyHPMod = enemySpawnerNode["HPMod"].as<float>();

    auto enemySpawnerComp = new ILM::EnemySpawner(enemyName, enemySpawnRateMod, enemySpeedMod, enemyDamageMod, enemyHPMod);

    for (YAML::Node enemies : enemySpawnerNode["enemies"])
    {
        auto enemyName = enemies["name"].as<std::string>();
        auto enemyType = enemies["type"].as<std::string>();
        std::string texturePath = getPathFromName(enemies["textureName"].as<std::string>());
        float speed = enemies["speed"].as<float>();
        float damage = enemies["damage"].as<float>();
        float HP = enemies["HP"].as<float>();
        float baseSpawnRate = enemies["baseSpawnRate"].as<float>();
        float scale = enemies["scale"].as<float>();

        enemySpawnerComp->addEnemy(enemyName, enemyType, texturePath, speed, HP, damage, baseSpawnRate, scale);
    }

    playerEntity->attachComponent(enemySpawnerComp);
    app->registerEntityAndAttachedComponents(playerEntity);
    return playerEntity;
}

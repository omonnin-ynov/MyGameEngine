#include "GameManager.h"

#include "EnemySpawner.h"
#include "TimedProjectileSpawner.h"
#include "MyGameEngine/Application.h"
#include "MyGameEngine/SpriteRendererComponent.h"

ILM::ILMResourceManager::ILMResourceManager()
{
}

MGE::AEntity* ILM::ILMResourceManager::instantiatePlayer(std::string name)
{
    //TODO this goes in a template unmarshal function

    auto app = MGE::Application::getInstance();
    MGE::AEntity* playerEntity{};
    for (YAML::Node player : _config["player"])
    {
        if (player["name"].as<std::string>() == name)
        {
            playerEntity = app->createEntity<MGE::AEntity>(player["name"].as<std::string>());
            // Get player Sprite
            auto spriteNode = player["sprite"];
            auto playerSprite = app->createComponentAndAttach<MGE::SpriteRendererComponent>(spriteNode["name"].as<std::string>(), playerEntity);
            playerSprite->loadAndSetTexture(getPathFromName(spriteNode["textureName"].as<std::string>()));

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
                    projectileInfo["baseSpawnRate"].as<float>());
            }

            app->registerComponent(projectileSpawner, playerEntity);
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

    app->registerComponent(enemySpawnerComp, playerEntity);
    return playerEntity;
}
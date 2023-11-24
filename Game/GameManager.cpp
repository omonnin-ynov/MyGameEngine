#include "GameManager.h"

#include "TimedProjectileSpawner.h"
#include "MyGameEngine/Application.h"
#include "MyGameEngine/SpriteRendererComponent.h"

ILM::ILMResourceManager::ILMResourceManager()
{
}

MGE::AEntity* ILM::ILMResourceManager::instantiatePlayer()
{
    auto app = MGE::Application::getInstance();
    MGE::AEntity* playerEntity{};
    for (YAML::Node player : _config["player"])
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
    return playerEntity;
}

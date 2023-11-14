#pragma once
#include "AComponent.h"
namespace MGE
{
    class TimedProjectileSpawner :
        public AComponent
    {
    protected:
        float _spawnRate;
        std::vector<>
    public:
        TimedProjectileSpawner(std::string name);
    };
}


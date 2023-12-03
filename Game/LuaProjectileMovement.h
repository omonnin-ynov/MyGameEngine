#pragma once
#include "MyGameEngine/ALuaScript.h"

namespace ILM
{
    class LuaProjectileMovement : public MGE::ALuaScript
    {
    public:
        LuaProjectileMovement(std::string name);

        void Awake() override;
        void Start() override;
        void Update(float deltaTime) override;
        void LateUpdate(float deltaTime) override;
    };
}


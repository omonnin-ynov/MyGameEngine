#pragma once
#include "MyGameEngine/LuaScript.h"

namespace ILM
{
    class LuaProjectileMovement : public MGE::LuaScript
    {
    public:
        LuaProjectileMovement(std::string name);
        void Update(float deltaTime) override;
    };
}


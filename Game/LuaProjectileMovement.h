#pragma once
#include "MyGameEngine/LuaScript.h"

namespace ILM
{
    class LuaProjectileMovement : public MGE::LuaScript
    {
    protected:
        lua_State* _luaState;
    public:
        LuaProjectileMovement(std::string name);
        void Update(float deltaTime) override;
    };
}


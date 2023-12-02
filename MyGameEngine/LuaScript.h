#pragma once
#include <lua.hpp>
#include <luabridge3/LuaBridge/LuaBridge.h>
#include "AComponent.h"

namespace MGE
{
    class LuaScript : public AComponent
    {
    public:
        LuaScript(std::string name);
        void Update(float deltaTime) override;
    };
}

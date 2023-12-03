#pragma once
#include <lua.hpp>
#include <luabridge3/LuaBridge/LuaBridge.h>
#include "AComponent.h"

namespace MGE
{
    class ALuaScript : public AComponent
    {
    protected:
        lua_State* _luaState;
    public:
        ALuaScript(std::string name);
    };
}

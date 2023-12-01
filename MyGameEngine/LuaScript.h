#pragma once
#include <lua.hpp>
#include <luabridge3/LuaBridge/LuaBridge.h>
#include "AComponent.h"

namespace MGE
{

    void printCPP(std::string text);
    class LuaScript : public AComponent
    {
    protected:
        lua_State* _luaState;
        void ReportErrors(lua_State* luaState, int status);
    public:
        LuaScript(std::string name);
        void SetScript(std::string scriptPath);
        virtual void Update(float deltaTime) override;
    };
}

#pragma once
#include <lua.hpp>
#include "luabridge3/LuaBridge/LuaBridge.h"
#include <string>

namespace MGE
{
	class LuaSystem
	{
	protected:
		lua_State* _luaState;

	protected:
		void ReportErrors(lua_State* luaState, int status);
	public:
		LuaSystem();
		void SetScript(std::string scriptPath);
		lua_State* getLuaState();
	};
}

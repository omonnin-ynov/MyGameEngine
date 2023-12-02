#include "LuaSystem.h"
#include "SFML/Graphics.hpp"

namespace ILM
{
	class Projectile;
}

namespace MGE
{
	class AEntity;
}

lua_State* MGE::LuaSystem::getLuaState()
{
	return _luaState;
}

void MGE::LuaSystem::ReportErrors(lua_State* luaState, int status)
{
    if (status == 0)
    {
        return;
    }

    std::cerr << "[LUA ERROR]" << lua_tostring(luaState, -1) << std::endl;
    // remove error from Lua state
    lua_pop(luaState, 1);
}

MGE::LuaSystem::LuaSystem()
{
    _luaState = luaL_newstate();
    luaL_openlibs(_luaState);

    luabridge::getGlobalNamespace(_luaState)
        .beginNamespace("sf")
			.beginClass<sf::Vector2f>("Vector2f")
		        .addConstructor<void(sf::Vector2f), void(float, float)>()
		        .addProperty("x", &sf::Vector2f::x, true)
		        .addProperty("y", &sf::Vector2f::y, true)
			.endClass()
	        .beginClass<sf::Transformable>("Transformable")
		        .addFunction("getPosition", &sf::Transformable::getPosition)
		        .addFunction("setPosition", static_cast<void (sf::Transformable::*)(const sf::Vector2f&)> (&sf::Transformable::setPosition))
		        .addFunction("getRotation", &sf::Transformable::getRotation)
		        .addFunction("setRotation", &sf::Transformable::setRotation)
		        .addFunction("move", static_cast<void (sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::move))
	        .endClass()
	        .beginClass<sf::Drawable>("Drawable")
	        .endClass()
		.endNamespace()
	    .beginNamespace("MGE")
	        .deriveClass<AEntity, sf::Transformable>("AEntity")
	        .endClass()
		.endNamespace()
	    .beginNamespace("ILM")
	        .deriveClass<ILM::Projectile, AEntity>("Projectile")
	        .endClass()
		.endNamespace();
}

void MGE::LuaSystem::SetScript(std::string scriptPath)
{
    // Load lua code
    int scriptLoadStatus = luaL_dofile(_luaState, scriptPath.c_str());

    // set error callback
    ReportErrors(_luaState, scriptLoadStatus);
}

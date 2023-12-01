#include "LuaScript.h"

#include "AEntity.h"

namespace ILM
{
    class Projectile;
}

void MGE::LuaScript::ReportErrors(lua_State* luaState, int status)
{
    if (status == 0)
    {
        return;
    }

    std::cerr << "[LUA ERROR]" << lua_tostring(luaState, -1) << std::endl;
    // remove error from Lua state
    lua_pop(luaState, 1);
}

void MGE::printCPP(std::string text)
{
    std::cout << text << std::endl;
}


MGE::LuaScript::LuaScript(std::string name) : AComponent(name)
{
    _luaState = luaL_newstate();
    luaL_openlibs(_luaState);

    luabridge::getGlobalNamespace(_luaState)
    .beginNamespace("sf")
        .addFunction("printCPP", &MGE::printCPP)
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
    .beginNamespace("MGE")
        .deriveClass<AEntity, sf::Transformable>("AEntity")
    .endClass()
    .beginNamespace("ILM")
        .deriveClass<ILM::Projectile, AEntity>("Projectile")
    .endClass();
}

void MGE::LuaScript::SetScript(std::string scriptPath)
{
    // Load lua code
    int scriptLoadStatus = luaL_dofile(_luaState, scriptPath.c_str());

    // set error callback
    ReportErrors(_luaState, scriptLoadStatus);
}

void MGE::LuaScript::Update(float deltaTime)
{
    AComponent::Update(deltaTime);
}

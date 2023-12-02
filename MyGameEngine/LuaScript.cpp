#include "LuaScript.h"

#include "AEntity.h"

namespace ILM
{
    class Projectile;
}

MGE::LuaScript::LuaScript(std::string name) : AComponent(name)
{
}

void MGE::LuaScript::Update(float deltaTime)
{
    AComponent::Update(deltaTime);
}

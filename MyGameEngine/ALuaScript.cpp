#include "ALuaScript.h"
#include "AComponent.h"
#include "Application.h"

namespace ILM
{
    class Projectile;
}

MGE::ALuaScript::ALuaScript(std::string name) : AComponent(name), _luaState(MGE::Application::getInstance()->getLua()->getLuaState())
{
    // I'm not sure if lua_state is ever going to be invalidated, I assume not
    // If it does turn out to be the case, I can always fetch it from application->getLua
}

void MGE::ALuaScript::Update(float deltaTime)
{
    AComponent::Update(deltaTime);
}

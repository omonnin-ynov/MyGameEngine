#include "LuaProjectileMovement.h"
#include "Projectile.h"
#include "MyGameEngine/Application.h"

ILM::LuaProjectileMovement::LuaProjectileMovement(std::string name) : ALuaScript(name)
{
}

void ILM::LuaProjectileMovement::Awake()
{
}

void ILM::LuaProjectileMovement::Start()
{
}

void ILM::LuaProjectileMovement::Update(float deltaTime)
{
    luabridge::LuaRef update = luabridge::getGlobal(_luaState, "update");
    auto parent = dynamic_cast<ILM::Projectile*>(MGE::Application::getInstance()->getParentEntity(this));

    try
    {
        luabridge::LuaResult res = update(deltaTime, parent, parent->getSpeed());
        for (int i = 0; i < res.size(); i++)
        {
            std::cout << res[i].isValid() << res[i].isNumber() << res[i] << std::endl;
        }

    }
    catch (luabridge::LuaException const& e)
    {
        std::cerr << e.what();
    }
}

void ILM::LuaProjectileMovement::LateUpdate(float deltaTime)
{
}

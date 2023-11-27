#pragma once
#include "MyGameEngine/ResourceManager.h"

namespace ILM
{
    class ILMResourceManager :
        public MGE::ResourceManager
    {
    protected:
        
    public:
        ILMResourceManager();

        MGE::AEntity* instantiatePlayer(std::string name);
    };
}

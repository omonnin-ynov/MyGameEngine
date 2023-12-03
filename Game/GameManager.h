#pragma once
#include "MyGameEngine/ResourceManager.h"

namespace ILM
{
    class ILMResourceManager :
        public MGE::ResourceManager
    {
    protected:
        
    public:
        ILMResourceManager() = default;
        // TODO fix this
        MGE::AEntity* instantiatePlayer(std::string name);
    };
}

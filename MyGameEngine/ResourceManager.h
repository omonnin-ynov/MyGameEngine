#pragma once
#include <yaml-cpp/yaml.h>
#include <SFML/Graphics.hpp>

namespace MGE {
    class ResourceManager
    {
    protected:
        static ResourceManager* _instance;
        YAML::Node _config;
        std::string _absolutePath;
        std::string _resPath;
        const std::string _yamlPath = "./config.yaml";
        std::map<std::string, std::string> _NameToPath;
        ResourceManager();

    public:
        static ResourceManager* getInstance();
        std::string getPathFromName(std::string name);
    };
}

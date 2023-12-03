#pragma once
#include <yaml-cpp/yaml.h>

namespace MGE {
    class AEntity;

    class ResourceManager
    {
    protected:
        static ResourceManager* _instance;
        YAML::Node _config;
        std::string _absolutePath;
        std::string _resPath;
        const std::string _yamlPath = "./config.yaml";
        std::map<std::string, std::string> _nameToPath;
        ResourceManager();

    public:
        static ResourceManager* getInstance();
        std::string getPathFromName(std::string name);
    };
}

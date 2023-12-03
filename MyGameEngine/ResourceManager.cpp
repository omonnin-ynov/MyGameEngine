#include <filesystem>
#include "ResourceManager.h"
#include "Application.h"
#include <Windows.h>

using namespace MGE;

ResourceManager* ResourceManager::_instance = nullptr;

/// \brief loads config.yaml and stores the resource paths
ResourceManager::ResourceManager() : _config(YAML::LoadFile("config.yaml")), _nameToPath()
{
    TCHAR buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, sizeof(buffer));
    _absolutePath = std::filesystem::path(buffer).parent_path().string();
    _resPath = "\\res\\";

    for (YAML::Node resource : _config["res"]) {
        _nameToPath[resource["name"].as<std::string>()] = resource["path"].as<std::string>();
    }
}

ResourceManager* ResourceManager::getInstance()
{
    if (!_instance) {
        _instance = new ResourceManager();
    }
    return _instance;
}

std::string ResourceManager::getPathFromName(std::string name)
{
    if (_nameToPath.find(name) != _nameToPath.end()) {
        return _absolutePath + _resPath + _nameToPath[name];
    }
    return "";
}

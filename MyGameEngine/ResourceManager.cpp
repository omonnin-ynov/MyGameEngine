#include <filesystem>
#include "ResourceManager.h"
#include <Windows.h>

using namespace MGE;

ResourceManager* ResourceManager::_instance = nullptr;

ResourceManager::ResourceManager() : _config(YAML::LoadFile("config.yaml")), _NameToPath()
{
	TCHAR buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, sizeof(buffer));
	_absolutePath = std::filesystem::path(buffer).parent_path().string();
	_resPath = ".\\res";

	for (YAML::Node resource : _config["res"]) {
		_NameToPath[resource["name"].as<std::string>()] = resource["path"].as<std::string>();
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
	if (_NameToPath.find(name) != _NameToPath.end()) {
		return  _resPath + _NameToPath[name];
	}
	return "";
}


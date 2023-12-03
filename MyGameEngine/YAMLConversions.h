#pragma once
#include <yaml-cpp/node/convert.h>
#include <yaml-cpp/node/node.h>

#include "Application.h"
#include "ResourceManager.h"
#include "SpriteRendererComponent.h"

namespace YAML {
    /// Unused for now, but may come in handy later
    template<>
    struct convert<MGE::SpriteRendererComponent> {
        static bool decode(const Node& node, MGE::SpriteRendererComponent& comp) {
            auto name = node["name"].as<std::string>();
            if (!node.IsSequence() || name.empty()) {
                return false;
            }
            comp = *MGE::Application::getInstance()->createComponent<MGE::SpriteRendererComponent>(name);
            auto texturePath = node["textureName"].as<std::string>();
            if (!texturePath.empty())
            {
                comp.loadAndSetTexture(MGE::ResourceManager::getInstance()->getPathFromName(texturePath));
            }
            return true;
        }
    };

    template<>
    struct convert<MGE::AEntity> {
        static bool decode(const Node& node, MGE::AEntity& comp) {
            auto name = node["name"].as<std::string>();
            if (!node.IsSequence() || name.empty()) {
                return false;
            }
            comp = *MGE::Application::getInstance()->createEntity<MGE::AEntity>(name);
            return true;
        }
    };
}
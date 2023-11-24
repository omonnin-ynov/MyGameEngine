#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace MGE {
    class AComponent {
    protected:
        uint64_t _ID;
        std::string _name;

    public:
        AComponent();
        AComponent(std::string name);

        virtual ~AComponent() = default;

        virtual void Awake();
        virtual void Start();
        virtual void Update(float deltaTime);
        virtual void LateUpdate(float deltaTime);
        uint64_t getID();
    };
}

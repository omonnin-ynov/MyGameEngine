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

        virtual void Awake() = 0;
        virtual void Start() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void LateUpdate(float deltaTime) = 0;
        uint64_t getID() const;
    };
}

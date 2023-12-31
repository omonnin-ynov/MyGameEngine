#pragma once
#include "IDamageable.h"
#include "MyGameEngine/AEntity.h"
#include "MyGameEngine/ICollidable.h"

namespace ILM
{
    class Projectile :
        public MGE::AEntity,
        public MGE::ICollidable,
		public IDamageable
    {
    protected:
        float _speed;
        float _areaMod;
        float _duration;
        // Self-destruct timer, used as spawn timer if projectile registered in TimedProjectileSpawner
        sf::Clock timer;

    public:
        Projectile(std::string name);

        Projectile(const std::string& name, float speed, float damage, float areaMod, float duration, float hp);

        void Awake() override;
        void Start() override;
        void Update(float deltaTime) override;

        float getSpeed() const;
        void setSpeed(float speed);
        float getElapsedTime();
        void resetTimer();

        // from ICollidable
        void BeginCollision(MGE::Collision collision) override;
        void EndCollision(MGE::Collision collision) override;

        // from IDamageable
        float takeDamage(MGE::AEntity* parent, float damage) override;
    };
}

#pragma once
#include "IDamageable.h"
#include "MyGameEngine/AEntity.h"
#include "MyGameEngine/ICollidable.h"

namespace ILM
{
    class Enemy :
        public MGE::AEntity,
        public MGE::ICollidable,
        public IDamageable
    {
    protected:
        float _speed;
        AEntity* _target;

    public:
        Enemy(std::string name);

        Enemy(std::string name, float speed, float hp, float damage, AEntity* target);

        void Awake() override;
        void Start() override;
        void Update(float deltaTime) override;

        float getSpeed() const;
        void setSpeed(float speed);
        AEntity* getTarget() const;
        void setTarget(AEntity* target);

        // From ICollidable
        void BeginCollision(MGE::Collision collision) override;
        void EndCollision(MGE::Collision collision) override;
        // from IDamageable
        float takeDamage(MGE::AEntity* parent, float damage) override;
    };
}

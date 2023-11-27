#pragma once
#include "MyGameEngine/AEntity.h"

namespace ILM
{
    class Enemy :
        public MGE::AEntity
    {
    protected:
        float _speed;
        float _hp;
        float _damage;
        AEntity* _target;

    public:
        Enemy(std::string name);

        Enemy(std::string name, float speed, float hp, float damage, AEntity* target);

        void Update(float deltaTime) override;

        float getSpeed() const;
        void setSpeed(float speed);
        float getHp() const;
        void removeHP(float hp);
        void setHp(float hp);
        AEntity* getTarget() const;
        void setTarget(AEntity* target);
    };
}

#pragma once
#include "box2d/box2d.h"

namespace MGE {
    class Collision
    {
    protected:
        b2Body* _selfComp;
        b2Body* _otherComp;

    public:
        Collision();
        Collision(b2Body* selfComp, b2Body* otherComp);

        b2Body* getSelfComp();
        b2Body* getOtherComp();

        void setSelfComp(b2Body* comp);
        void setOtherComp(b2Body* comp);
    };
}


#include "Collision.h"

MGE::Collision::Collision() : _selfComp(), _otherComp()
{
}

MGE::Collision::Collision(b2Body* selfComp, b2Body* otherComp) : _selfComp(selfComp), _otherComp(otherComp)
{
}

b2Body* MGE::Collision::getSelfComp()
{
    return _selfComp;
}

b2Body* MGE::Collision::getOtherComp()
{
    return _otherComp;
}

void MGE::Collision::setSelfComp(b2Body* comp)
{
    _selfComp = comp;
}

void MGE::Collision::setOtherComp(b2Body* comp)
{
    _otherComp = comp;
}

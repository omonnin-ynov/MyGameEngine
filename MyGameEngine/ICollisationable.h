#pragma once
namespace MGE {

    class ICollisationable
    {
    public:
        virtual void BeginCollision() = 0;
        virtual void EndCollision() = 0;
    };
}

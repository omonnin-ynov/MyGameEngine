#pragma once
#include "box2d/box2d.h"

namespace MGE {
	class AEntity;
	class RigidBodyComponent;

	class Collision
    {
    protected:
        b2Body* _selfb2Body;
		RigidBodyComponent* _selfRigidBody;
		AEntity* _selfParent;

		b2Body* _otherb2Body;
		RigidBodyComponent* _otherRigidBody;
		AEntity* _otherParent;

    public:
        Collision();

        Collision(b2Body* selfb2_body, RigidBodyComponent* self_rigid_body, AEntity* self_parent, b2Body* otherb2_body,
            RigidBodyComponent* other_rigid_body, AEntity* other_parent);

        b2Body* getSelfb2Body() const;
        RigidBodyComponent* getSelfRigidBody() const;
        AEntity* getSelfParent() const;
        b2Body* getOtherb2Body() const;
        RigidBodyComponent* getOtherRigidBody() const;
        AEntity* getOtherParent() const;
    };
}


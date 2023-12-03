#include "Collision.h"

MGE::Collision::Collision(b2Body* selfb2_body, RigidBodyComponent* self_rigid_body, AEntity* self_parent, b2Body* otherb2_body,
	RigidBodyComponent* other_rigid_body, AEntity* other_parent)
	: _selfb2Body(selfb2_body),
	_selfRigidBody(self_rigid_body),
	_selfParent(self_parent),
	_otherb2Body(otherb2_body),
	_otherRigidBody(other_rigid_body),
	_otherParent(other_parent)
{
}

b2Body* MGE::Collision::getSelfb2Body() const
{
	return _selfb2Body;
}

MGE::RigidBodyComponent* MGE::Collision::getSelfRigidBody() const
{
	return _selfRigidBody;
}

MGE::AEntity* MGE::Collision::getSelfParent() const
{
	return _selfParent;
}

b2Body* MGE::Collision::getOtherb2Body() const
{
	return _otherb2Body;
}

MGE::RigidBodyComponent* MGE::Collision::getOtherRigidBody() const
{
	return _otherRigidBody;
}

MGE::AEntity* MGE::Collision::getOtherParent() const
{
	return _otherParent;
}
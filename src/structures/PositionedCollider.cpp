#include "PositionedCollider.h"

PositionedCollider::PositionedCollider(
	const cat::Entity entity,
	const Collider& collider,
	const cat::Transform& transform
	)
{
	this->objet_position = transform.position;
	this->object_rotation = transform.transformMatrix.ReduceDimensions();
	this->position = collider.pos;
	this->rotation = collider.rotation;
	this->entity = entity;
	dimensions = cat::Vector<float, 3> { collider.width, collider.height, collider.length };
	
	true_position = objet_position + position;
	true_rotation = object_rotation * rotation;
}
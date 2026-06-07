#pragma once
#include "cat/cat.h"
#include "Collider.h"
#include <optional>

struct PositionedCollider 
{
	cat::Vector<float, 3> objet_position;
	cat::Matrix<float, 3> object_rotation;
	cat::Vector<float, 3> position;
	cat::Matrix<float, 3> rotation;
	cat::Vector<float, 3> true_position;
	cat::Matrix<float, 3> true_rotation;
	cat::Vector<float, 3> dimensions;
	std::optional<cat::Entity> entity;
	
	PositionedCollider(
	const cat::Entity entity,
	const Collider& collider,
	const cat::Transform& transform = cat::Transform()
	);
};
#pragma once
#include "GlobalInclude.h"
#include <memory>
#include <vector>
#include "Collider.h"
#include "Ray.h"
#include "PositionedCollider.h"
#include "cat/cat.h"

class SpaceshipGame;

class PhysicsSystem
{
private:
    const float COLLIDERS_TOO_FAR_DISTANCE = 20;

    bool RayIntersectsAABB(const PositionedCollider col, const Ray& ray);

    bool RayCast(const PositionedCollider col, const Ray ray);

    bool SAT(const PositionedCollider col1, const PositionedCollider col2);

    bool IsSeperationPlane(const cat::Vector<float, 3>& relativePos, const cat::Vector<float, 3> plane, const PositionedCollider& col1, const PositionedCollider& col2);
	
	std::vector<PositionedCollider> GetAllColliders(SpaceshipGame* game);
	
public:
    void CheckCollisions(SpaceshipGame* game);

    void ShootLaser(Ray fireRay, SpaceshipGame* game); 

};

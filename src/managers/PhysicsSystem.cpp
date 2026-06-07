#include "PhysicsSystem.h"
#include "SpaceshipGame.h"
#include <memory>
#include <cmath> 
#include <algorithm>
#include <span>

std::vector<PositionedCollider> PhysicsSystem::GetAllColliders(SpaceshipGame* game)
{
	std::span<const cat::Entity> colliders = game->GetAllEntitiesWithComponent<Collider>();
    int n = colliders.size();
    
	std::vector<PositionedCollider> full_colliders;
	full_colliders.reserve(colliders.size());
	for(int i = 0; i < n; i++)
    {
		Collider& collider = colliders[i].GetComponent<Collider>(game);
        if(colliders[i].HasComponent<cat::Transform>(game))
		{
			cat::Transform& transform = colliders[i].GetComponent<cat::Transform>(game);
			full_colliders.push_back(PositionedCollider(
				colliders[i],
				collider,
				transform
			));
		} else {
			full_colliders.push_back(PositionedCollider(
				colliders[i],
				collider
			));
		}
    }
	
	return full_colliders;
}

void PhysicsSystem::CheckCollisions(SpaceshipGame* game)
{
	std::vector<PositionedCollider> colliders = GetAllColliders(game);
	int n = colliders.size();
    for(int i = 0; i < n; i++)
    {   
        for(int j = i+1; j < n; j++)
        {
            if((colliders[i].true_position - colliders[j].true_position).Magnitude() < COLLIDERS_TOO_FAR_DISTANCE)
            {
                if(SAT(colliders[i], colliders[j]))
                {
					//LOG("TODO collision");
                    //game->KillSpaceship(colliders[j].entityId);
                    //game->KillSpaceship(colliders[i].entityId);
                }
            }
        }
    }
}

void PhysicsSystem::ShootLaser(Ray fireRay, SpaceshipGame* game)
{
    std::vector<PositionedCollider> colliders = GetAllColliders(game);
	int n = colliders.size();
    for (int i = 0; i < n; i++)
    {
        if(fireRay.shooterEntity.entity != colliders[i].entity)
		{
            if(RayCast(colliders[i], fireRay))
            {
				LOG("TODO spacheip shot");
                //game->KillSpaceship(colliders[i].entityId);
            }
        }
    }
}

bool PhysicsSystem::SAT(const PositionedCollider col1, const PositionedCollider col2)
{
    cat::Vector<float, 3> relativePos = col1.true_position - col2.true_position;

    if(IsSeperationPlane(relativePos, col1.true_rotation.GetCol(0),    col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.true_rotation.GetCol(1),    col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.true_rotation.GetCol(2),    col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col2.true_rotation.GetCol(0),    col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col2.true_rotation.GetCol(1),    col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col2.true_rotation.GetCol(2),    col1, col2)) return false;
    
    if(IsSeperationPlane(relativePos, col1.true_rotation.GetCol(0) * col2.true_rotation.GetCol(0),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.true_rotation.GetCol(0) * col2.true_rotation.GetCol(1),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.true_rotation.GetCol(0) * col2.true_rotation.GetCol(2),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.true_rotation.GetCol(1) * col2.true_rotation.GetCol(0),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.true_rotation.GetCol(1) * col2.true_rotation.GetCol(1),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.true_rotation.GetCol(1) * col2.true_rotation.GetCol(2),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.true_rotation.GetCol(2) * col2.true_rotation.GetCol(0),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.true_rotation.GetCol(2) * col2.true_rotation.GetCol(1),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.true_rotation.GetCol(2) * col2.true_rotation.GetCol(2),         col1, col2)) return false;

    return true;
}

bool PhysicsSystem::IsSeperationPlane(const cat::Vector<float, 3>& relativePos, const cat::Vector<float, 3> plane, 
const PositionedCollider& col1, const PositionedCollider& col2)
{
    return (fabs(relativePos % plane) > 
        (
            fabs(col1.true_rotation.GetCol(0) * (col1.dimensions.x()  / 2)  % plane) + 
            fabs(col1.true_rotation.GetCol(1) * (col1.dimensions.y() / 2)  % plane) +
            fabs(col1.true_rotation.GetCol(2) * (col1.dimensions.z() / 2)  % plane) +
            fabs(col2.true_rotation.GetCol(0) * (col2.dimensions.x()  / 2)  % plane) + 
            fabs(col2.true_rotation.GetCol(1) * (col2.dimensions.y() / 2)  % plane) + 
            fabs(col2.true_rotation.GetCol(2) * (col2.dimensions.z() / 2)  % plane)
        )
    );
}

bool PhysicsSystem::RayCast(const PositionedCollider col, const Ray ray)
{
    cat::Matrix<float, 3> transposedRotMat = col.true_rotation.Transpose();
    Ray transformedRay(ray.shooterEntity, transposedRotMat * (ray.origin - col.true_position), transposedRotMat * ray.direction);
	return RayIntersectsAABB(col, transformedRay);
}

bool PhysicsSystem::RayIntersectsAABB(const PositionedCollider col, const Ray& ray) 
{
    float tMin = -INFINITY;
    float tMax = INFINITY;
    
    cat::Vector<float, 3> boxMin = {
        -col.dimensions.x() / 2.0f,
        -col.dimensions.y() / 2.0f,
        -col.dimensions.z() / 2.0f
    };

    cat::Vector<float, 3> boxMax = {
        col.dimensions.x() / 2.0f,
        col.dimensions.y() / 2.0f,
        col.dimensions.z() / 2.0f
    };

    for (int i = 0; i < 3; ++i) {
        float origin = ray.origin.data[i];
        float dir = ray.direction.data[i];
        float minB = boxMin.data[i];
        float maxB = boxMax.data[i];

        if (std::abs(dir) < 1e-8f) {
            // Ray is parallel to slab. No hit if origin not within slab
            if (origin < minB || origin > maxB)
            {
                return false;
            }
        } 
        else 
        {
            float t1 = (minB - origin) / dir;
            float t2 = (maxB - origin) / dir;

            if (t1 > t2) std::swap(t1, t2);
            tMin = std::max(tMin, t1);
            tMax = std::min(tMax, t2);

            if (tMin > tMax || tMax < 0)
                return false;
        }
    }

    return true;
}

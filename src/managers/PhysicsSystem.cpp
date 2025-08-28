#include "PhysicsSystem.h"
#include "Game.h"
#include <memory>
#include <cmath> 
#include <algorithm>

void PhysicsSystem::AddCollider(unsigned int id, Vector<float, 3> pos, Vector<float, 3> dimensions)
{
    Collider col;
    col.entityId = id;
    col.pos = pos;
    col.width = dimensions.x();
    col.height = dimensions.y();
    col.length = dimensions.z();
    Matrix<float, 3> rotation;
    colliders.push_back(col);
}

void PhysicsSystem::CheckCollisions(Game* game)
{
    int n = colliders.size();
    
    for(int i = 0; i < n; i++)
    {
        weak_ptr<Spaceship> ship = game->GetSpaceShip(colliders[i].entityId);
        colliders[i].pos = ship.lock()->position;
        colliders[i].rotation = ship.lock()->transformMatrix.ReduceDimensions();
    }

    for(int i = 0; i < n; i++)
    {   
        for(int j = i+1; j < n; j++)
        {
            if((colliders[i].pos - colliders[j].pos).Magnitude() < COLLIDERS_TOO_FAR_DISTANCE)
            {
                if(SAT(colliders[i], colliders[j]))
                {
                    game->KillSpaceship(colliders[j].entityId);
                    game->KillSpaceship(colliders[i].entityId);
                }
            }
        }
    }
}

void PhysicsSystem::ShootLaser(Ray fireRay, Game* game)
{
    int n = colliders.size();
    for (int i = 0; i < n; i++)
    {
        if(fireRay.shooterId != colliders[i].entityId){
            if(RayCast(colliders[i], fireRay))
            {
                game->KillSpaceship(colliders[i].entityId);
            }
        }
    }
}

bool PhysicsSystem::SAT(const Collider col1, const Collider col2)
{
    Vector<float, 3> relativePos = col1.pos - col2.pos;

    if(IsSeperationPlane(relativePos, col1.rotation.GetCol(0),    col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.rotation.GetCol(1),    col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.rotation.GetCol(2),    col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col2.rotation.GetCol(0),    col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col2.rotation.GetCol(1),    col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col2.rotation.GetCol(2),    col1, col2)) return false;
    
    if(IsSeperationPlane(relativePos, col1.rotation.GetCol(0) * col2.rotation.GetCol(0),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.rotation.GetCol(0) * col2.rotation.GetCol(1),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.rotation.GetCol(0) * col2.rotation.GetCol(2),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.rotation.GetCol(1) * col2.rotation.GetCol(0),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.rotation.GetCol(1) * col2.rotation.GetCol(1),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.rotation.GetCol(1) * col2.rotation.GetCol(2),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.rotation.GetCol(2) * col2.rotation.GetCol(0),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.rotation.GetCol(2) * col2.rotation.GetCol(1),         col1, col2)) return false;
    if(IsSeperationPlane(relativePos, col1.rotation.GetCol(2) * col2.rotation.GetCol(2),         col1, col2)) return false;

    return true;
}

bool PhysicsSystem::IsSeperationPlane(const Vector<float, 3>& relativePos, const Vector<float, 3> plane, const Collider& col1, const Collider& col2)
{
    return (fabs(relativePos % plane) > 
        (
            fabs(col1.rotation.GetCol(0) * (col1.width  / 2)  % plane) + 
            fabs(col1.rotation.GetCol(1) * (col1.height / 2)  % plane) +
            fabs(col1.rotation.GetCol(2) * (col1.length / 2)  % plane) +
            fabs(col2.rotation.GetCol(0) * (col2.width  / 2)  % plane) + 
            fabs(col2.rotation.GetCol(1) * (col2.height / 2)  % plane) + 
            fabs(col2.rotation.GetCol(2) * (col2.length / 2)  % plane)
        )
    );
}

bool PhysicsSystem::RayCast(const Collider col, const Ray ray)
{   
    Ray transformedRay;
    transformedRay.origin = ray.origin - col.pos;
    Matrix<float, 3> transposedRotMat = col.rotation.Transpose();
    transformedRay.origin = transposedRotMat * transformedRay.origin;
    transformedRay.direction = transposedRotMat * ray.direction;
    return RayIntersectsAABB(col, transformedRay);
}


bool PhysicsSystem::RayIntersectsAABB(const Collider col, const Ray& ray) {
    float tMin = -INFINITY;
    float tMax = INFINITY;
    
    Vector<float, 3> boxMin = {
        -col.width / 2.0f,
        -col.height / 2.0f,
        -col.length / 2.0f
    };

    Vector<float, 3> boxMax = {
        col.width / 2.0f,
        col.height / 2.0f,
        col.length / 2.0f
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

Collider& PhysicsSystem::GetFirstColliderBelongingTo(unsigned int id)
{
    int n = colliders.size();
    for (int i = 0; i < n; i++)
    {
        if(colliders[i].entityId == id)
        {
            return colliders[i];
        }
    }
    error("error");
}


void PhysicsSystem::MarkColliderForDeletion(unsigned int entityId)
{
    collidersToKill.emplace_back(entityId);
}

void PhysicsSystem::RemoveCollider(unsigned int entityId)
{
    colliders.erase(
        std::remove_if(
            colliders.begin(),
            colliders.end(),
            [entityId](const Collider& c) {
                return c.entityId == entityId;
            }),
        colliders.end()
    );
}

void PhysicsSystem::Cleanup()
{
    int n = collidersToKill.size();
    for (int i = 0; i < n; i++)
    {
        RemoveCollider(collidersToKill[i]);
    }
}

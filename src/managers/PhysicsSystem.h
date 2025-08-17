#pragma once
#include "GlobalInclude.h"
#include "advancedMath.h"
#include <memory>
#include <vector>
#include "Collider.h"

class Game;

class PhysicsSystem
{
private:
    const float COLLIDERS_TOO_FAR_DISTANCE = 20;
    std::vector<Collider> colliders;
    std::vector<unsigned int> collidersToKill;

    bool RayIntersectsAABB(const Collider col, const Ray& ray);

    bool RayCast(const Collider col, const Ray ray);

    bool SAT(const Collider col1, const Collider col2);

    bool IsSeperationPlane(const vector3& relativePos, const vector3 plane, const Collider& col1, const Collider& col2);
    
    void RemoveCollider(unsigned int entityId);
public:
    void AddCollider(unsigned int id, vector3 pos, vector3 dimensions);

    void CheckCollisions(Game* game);

    void ShootLaser(Ray fireRay, Game* game);

    Collider& GetFirstColliderBelongingTo(unsigned int id);

    void MarkColliderForDeletion(unsigned int entityId);

    void Cleanup();
};
#pragma once
#include "GlobalInclude.h"
#include "advancedMath.h"
#include <memory>

struct PhysicsData
{
    vector3 velocity;
    vector3 angularVelocity;
    
    void AddVelocity(vector3 direction, float amount);
    
    void AddAngularVelocity(vector3 axis, float amount);
};
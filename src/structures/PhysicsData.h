#pragma once
#include "GlobalInclude.h"
#include "advancedMath.h"
#include <memory>

struct PhysicsData
{
    Vector<float, 3> velocity;
    Vector<float, 3> angularVelocity;
    
    void AddVelocity(Vector<float, 3> direction, float amount);
    
    void AddAngularVelocity(Vector<float, 3> axis, float amount);
};
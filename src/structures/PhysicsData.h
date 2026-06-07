#pragma once
#include "GlobalInclude.h"
#include "cat/cat.h"
#include <memory>

struct PhysicsData
{
    cat::Vector<float, 3> velocity;
    cat::Vector<float, 3> angularVelocity;
    
    void AddVelocity(cat::Vector<float, 3> direction, float amount);
    
    void AddAngularVelocity(cat::Vector<float, 3> axis, float amount);
};

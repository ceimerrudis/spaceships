#pragma once
#include "GlobalInclude.h"
#include "advancedMath.h"
#include <memory>

struct Ray {
    unsigned int shooterId;
    vector3 origin;
    vector3 direction;
};

struct Collider
{
    unsigned int entityId;
    vector3 pos;
    float width;
    float height;
    float length;
    matrix3 rotation;
};
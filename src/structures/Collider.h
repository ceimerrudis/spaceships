#pragma once
#include "GlobalInclude.h"
#include "advancedMath.h"
#include <memory>

struct Ray {
    unsigned int shooterId;
    Vector<float, 3> origin;
    Vector<float, 3> direction;
};

struct Collider
{
    unsigned int entityId;
    Vector<float, 3> pos;
    float width;
    float height;
    float length;
    Matrix<float, 3> rotation;
};
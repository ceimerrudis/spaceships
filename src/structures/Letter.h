#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"

struct Letter
{
    int offset;
    Vector<int, 2> size;
    std::shared_ptr<unsigned int> textureKey;
};
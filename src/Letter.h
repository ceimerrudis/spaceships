#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"

struct Letter
{
    int offset;
    vector2i size;
    std::shared_ptr<unsigned int> textureKey;
};
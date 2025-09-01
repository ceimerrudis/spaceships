#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include "Renderable.h"
#include <array>

struct ModelTexture
{
    #if DEBUG
        bool initialized;
    #endif
    std::shared_ptr<unsigned int> textureKey;
};

void InitModelTexture(ModelTexture& modelTexture, std::shared_ptr<unsigned int> textureKey);

#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include "Renderable.h"
#include <array>

struct ImageData
{
    #if DEBUG
        bool initialized;
    #endif
    std::shared_ptr<unsigned int> textureKey;
    std::array<float, 16> vertexes;
};

void InitImageData(ImageData& imageData, Renderable& renderable, bool IsText = false);
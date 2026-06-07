#pragma once
#include "cat/Game.h"
#include "cat/AdvancedMath.h"
#include "cat/Renderable.h"
#include <array>

namespace cat
{
class ImageData
{
public:
    std::shared_ptr<unsigned int> textureKey;
    std::array<float, 16> vertexes;
	
	ImageData(Renderable& renderable, bool IsText = false);
};
}

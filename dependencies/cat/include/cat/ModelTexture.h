#pragma once
#include <array>
#include "cat/Game.h"
#include "cat/AdvancedMath.h"
#include "cat/Renderable.h"

namespace cat 
{
struct ModelTexture
{
public:
    std::shared_ptr<unsigned int> textureKey;
	
	ModelTexture(std::shared_ptr<unsigned int> textureKey);
};
}

#pragma once
#include <array>
#include <memory>
#include "cat/Game.h"
#include "cat/Renderable.h"
#include "cat/MeshData.h"

namespace cat
{
//Requires MeshData
struct Shading
{
public:
	std::unique_ptr<unsigned int[]> normalIndexes;//pointer to a condensed list of normal indicies (condensed meaning one int per trig instead of vertex)
    std::shared_ptr<unsigned int> normalsBufferKey;
    std::shared_ptr<unsigned int> normalIndexesBufferKey;
	
	Shading(Game * game, Renderable& renderable, MeshData& meshData);
};
}

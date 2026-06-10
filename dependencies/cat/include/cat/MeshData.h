#pragma once
#include <array>
#include <memory>
#include "cat/Game.h"
#include "cat/AdvancedMath.h"
#include "cat/Renderable.h"
#include "cat/Mesh.h"

namespace cat 
{
struct MeshData
{
public:
    std::shared_ptr<Mesh> meshP;
	
	MeshData(Renderable& renderable, std::shared_ptr<Mesh> mesh);
};
}

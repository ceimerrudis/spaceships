#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "Renderable.h"
#include <memory>
#include "MeshData.h"
#include "Entity.h"
#include "Transform.h"
#include "ModelTexture.h"

namespace cat
{
class Game;
class CubemapObject
{
public:
    Entity entity;

    CubemapObject(Game* game, const std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shaders, std::array<uint64_t, 6> textureKeys); 
};
}

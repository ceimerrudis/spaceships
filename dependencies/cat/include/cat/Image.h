#pragma once
#include <array>
#include "cat/AdvancedMath.h"
#include "cat/Renderable.h"
#include "cat/ImageData.h"
#include "cat/UITransform.h"
#include "cat/Entity.h"
#include "cat/Shader.h"

namespace cat
{
class Game;
class Image
{
public:
    Entity entity;

    Image(Game* game, std::shared_ptr<Shader> shaders, uint64_t textureResourceKey);
    
    ~Image();

    void SetPosition();

    void SetSize();
};
}

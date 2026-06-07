#pragma once
#include <memory>
#include "cat/Interactable.h"
#include "cat/Shader.h"
#include "cat/Entity.h"

namespace cat
{
class Game;
class Button
{
public:
    Entity entity;
    
    Button(Game* game, std::shared_ptr<Shader> shaders, uint64_t textureAssetId, Function onClickFunction, FunctionData onClickData);
    
    ~Button();
};
}

#pragma once
#include "cat/Letter.h"
#include "cat/Entity.h"
#include "cat/TextData.h"
#include "cat/ImageData.h"
#include "cat/Renderable.h" 
#include "cat/UITransform.h"
#include <vector>
#include <memory>

namespace cat 
{
class Game;
class TextObject
{
public:
    Entity entity;

    TextObject(Game* game, std::shared_ptr<Shader> shaders);
};
}

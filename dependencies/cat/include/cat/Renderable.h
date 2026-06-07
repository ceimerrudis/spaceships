#pragma once
#include <memory>
#include "cat/Game.h"
#include "cat/Shader.h"

namespace cat 
{
struct Renderable 
{
public:
    std::shared_ptr<unsigned int> vertexArrayObjectKey;
    std::shared_ptr<unsigned int> vertexBufferKey;
    std::shared_ptr<unsigned int> indexBufferKey;

    unsigned int trigCount;
    unsigned int vertexCount;

    std::shared_ptr<Shader> shaders;
	
	Renderable(Game* game, std::shared_ptr<Shader> shaders);
};
}

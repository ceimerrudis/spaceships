#pragma once
#include "GlobalInclude.h"
#include "Shader.h"
#include "OpenGLResourceLibrary.h"
#include <memory>

struct Renderable 
{
    #if DEBUG
        bool initialized;
    #endif
    std::shared_ptr<unsigned int> vertexArrayObjectKey;
    std::shared_ptr<unsigned int> vertexBufferKey;
    std::shared_ptr<unsigned int> indexBufferKey;

    unsigned int trigCount;
    unsigned int vertexCount;

    std::shared_ptr<Shader> shaders;
};

void InitRenderable(Renderable& renderable, std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib);

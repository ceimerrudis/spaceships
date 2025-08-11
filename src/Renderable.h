#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include "WorldObject.h"
#include "TextureManager.h"
#include "Shader.h"
#include <array>

struct Renderable: public WorldObject{
public:
    std::shared_ptr<unsigned int> vertexArrayObjectKey;//gened automaticaly
    std::shared_ptr<unsigned int> vertexBufferKey;//gened automaticaly
    std::shared_ptr<unsigned int> indexBufferKey;//gened automaticaly
    std::shared_ptr<unsigned int> textureKey;
    std::shared_ptr<TextureManager> textureManager;

    unsigned int trigCount;
    unsigned int vertexCount;

    std::shared_ptr<Shader> shaders;

    Renderable(std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib);

    ~Renderable();

    virtual void Render() = 0;
};
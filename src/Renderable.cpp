#include "GlobalInclude.h"
#include "GLerrorHandling.h"
#include "AdvancedMath.h"
#include "WorldObject.h"
#include "Renderable.h"

Renderable::Renderable(std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib)
:   WorldObject()
{
    this->shaders = shaders;
    vertexBufferKey = glResLib.CreateBuffer();
    indexBufferKey = glResLib.CreateBuffer();
    vertexArrayObjectKey = glResLib.CreateVertexArrayObject();
}

Renderable::~Renderable()
{
    if(textureKey != nullptr)
    {
        textureManager->ReleaseTexture(textureKey);
    }
}
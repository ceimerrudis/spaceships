#include "Renderable.h"
#include "OpenGLResourceLibrary.h"

void InitRenderable(Renderable& renderable, std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib)
{
    #if DEBUG
        renderable.initialized = true;
    #endif
    renderable.shaders = shaders;
    renderable.vertexBufferKey = glResLib.CreateBuffer();
    renderable.indexBufferKey = glResLib.CreateBuffer();
    renderable.vertexArrayObjectKey = glResLib.CreateVertexArrayObject();
}

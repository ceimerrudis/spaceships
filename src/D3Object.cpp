#include "D3Object.h"
#include "Logger.h"
#include "WorldObject.h"
#include "GLerrorHandling.h"
#include <math.h>
#include <iostream>
#include <array>
#include "AdvancedMath.h"
#include "ObjectLoader.h"
#include "glad/glad.h"
#include "TextureManager.h"
#include "TextureResource.h"
#include <memory>

D3Object::D3Object(const std::shared_ptr<solar::Mesh> mesh, std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib)
:   Renderable(shaders, glResLib),
    meshP(mesh)
{
    trigCount = meshP->vertexIndices.size() / 3;
    vertexCount = meshP->vertices.size();
    
    GL(glBindVertexArray(*vertexArrayObjectKey));

    GL(glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferKey));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBufferKey));

    GL(glBufferData(GL_ARRAY_BUFFER         , vertexCount * sizeof(float)         , meshP->vertices.data()     , GL_STATIC_DRAW));
    GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER , trigCount   * 3 * sizeof(unsigned int)  , meshP->vertexIndices.data()       , GL_STATIC_DRAW));

    GL(glEnableVertexAttribArray(0));
    GL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));

    GL(glBindVertexArray(0));
    GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL(glDisableVertexAttribArray(0));
}
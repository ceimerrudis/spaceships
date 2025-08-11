#include "CubemapObject.h"
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

void CubemapObject::Render()
{
    GL(glDepthMask(GL_FALSE));
    GLuint tex = textureManager->LoadTexture(textureKey);
    shaders->AssignDataToUniform(SKYBOX_TEXTURE_SLOT, &tex);
    GL(glBindVertexArray(*vertexArrayObjectKey));
    GL(glDrawElements(GL_TRIANGLES, trigCount*3, GL_UNSIGNED_INT, NULL));

    GL(glDepthMask(GL_TRUE));
    GL(glBindVertexArray(0));
}

CubemapObject::CubemapObject(const std::shared_ptr<solar::Mesh> mesh, std::shared_ptr<Shader> shaders,  std::array<TaggedTextureResource*, 6> textures, std::shared_ptr<TextureManager> textureManager, OpenGLResourceLibrary& glResLib) 
:   D3Object(mesh, shaders, glResLib)
{
    this->textureManager = textureManager;
    textureKey = textureManager->AddCubemapTexture(GL_TEXTURE_CUBE_MAP, textures);
}
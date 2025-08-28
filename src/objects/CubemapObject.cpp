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

CubemapObject::CubemapObject(const std::shared_ptr<solar::Mesh> mesh, std::shared_ptr<Shader> shaders,  std::array<TaggedTextureResource*, 6> textures, std::shared_ptr<TextureManager> textureManager, OpenGLResourceLibrary& glResLib) 
:   D3Object(mesh, shaders, glResLib)
{
    textureKey = textureManager->AddCubemapTexture(GL_TEXTURE_CUBE_MAP, textures);
}
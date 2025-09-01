#pragma once
#include "GlobalInclude.h"
#include "ObjectLoader.h"
#include "Renderable.h"
#include "TextureManager.h"
#include <memory>
#include "MeshData.h"
#include "Entity.h"
#include "Transform.h"
#include "ModelTexture.h"

class CubemapObject
{
public:
    Entity entity;
    MeshData meshData;
    Renderable renderable;
    Transform transform;
    ModelTexture modelTexture;

    CubemapObject(const std::shared_ptr<solar::Mesh> mesh, std::shared_ptr<Shader> shaders,  
        std::array<TaggedTextureResource*, 6> textures, std::shared_ptr<TextureManager> textureManager, OpenGLResourceLibrary& glResLib); 
};
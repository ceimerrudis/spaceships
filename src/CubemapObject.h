#pragma once
#include "GlobalInclude.h"
#include "D3Object.h"
#include "WorldObject.h"
#include "ObjectLoader.h"
#include "Renderable.h"
#include "TextureManager.h"
#include <memory>

struct CubemapObject: public D3Object{
public:

    void Render() override;
    
    CubemapObject(const std::shared_ptr<solar::Mesh> mesh, std::shared_ptr<Shader> shaders,  std::array<TaggedTextureResource*, 6> textures, std::shared_ptr<TextureManager> textureManager, OpenGLResourceLibrary& glResLib); 
};
#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include "WorldObject.h"
#include "TextureManager.h"
#include "Renderable.h"
#include <array>

struct D2Object: public Renderable{
public:
    std::array<float, 16> vertexes;
    std::array<unsigned int, 6> indicies;

    void Render() override;

    D2Object(std::shared_ptr<Shader> shaders, vector2 bottomLeft, vector2 topRight, TextureResource& textureResource, std::shared_ptr<TextureManager> textureManager, OpenGLResourceLibrary& glResLib);
    
    ~D2Object();
};
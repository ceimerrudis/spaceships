#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include "WorldObject.h"
#include "ObjectLoader.h"
#include "Renderable.h"
#include "TextureManager.h"
#include <memory>

struct D3Object: public Renderable{
public:
    const std::shared_ptr<solar::Mesh> meshP;

    D3Object(const std::shared_ptr<solar::Mesh> mesh, std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib);
};
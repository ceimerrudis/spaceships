#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include "D3Object.h"
#include "WorldObject.h"
#include "ObjectLoader.h"
#include "Renderable.h"
#include "TextureManager.h"
#include <memory>

struct ModelObject: public D3Object{
public:
    unsigned int* normalIndexes;
    std::shared_ptr<unsigned int> normalsBufferKey;//OpenGL lieta
    std::shared_ptr<unsigned int> normalIndexesBufferKey;//OpenGL lieta

    unsigned int normalCount;

    void Render() override;

    ModelObject(const std::shared_ptr<solar::Mesh> mesh, std::shared_ptr<Shader> shaders, OpenGLResourceLibrary& glResLib);
};
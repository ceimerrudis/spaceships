#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include "Renderable.h"
#include "MeshData.h"
#include "OpenGLResourceLibrary.h"
#include <array>
#include <memory>

struct Shading
{
    #if DEBUG
        bool initialized;
    #endif
    unsigned int* normalIndexes;
    std::shared_ptr<unsigned int> normalsBufferKey;
    std::shared_ptr<unsigned int> normalIndexesBufferKey;
    unsigned int normalCount;
};

void InitShading(Shading& shading, Renderable& renderable, MeshData& meshData, OpenGLResourceLibrary& glResLib);
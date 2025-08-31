#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include <array>
#include "ObjectLoader.h"
#include "Renderable.h"

struct MeshData
{
    #if DEBUG
        bool initialized;
    #endif
    std::shared_ptr<solar::Mesh> meshP;
};

void InitMeshData(MeshData& meshData, Renderable& renderable, const std::shared_ptr<solar::Mesh> mesh);
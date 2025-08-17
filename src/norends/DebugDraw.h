#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"
#include <vector>

class DebugDraw {
    bool line;
    unsigned int vertexArrayObjectKey;
    unsigned int vertexBufferKey;
    unsigned int indexBufferKey;
    unsigned int trigCount;
    unsigned int vertexCount;
    unsigned int shaderKey;

    unsigned int worldTransfUniformLoc;
    unsigned int viewMatUniformLoc;
    unsigned int projMatUniformLoc;
    unsigned int colorLoc;

    std::vector<float> vertices;
    std::vector<unsigned int > vertexIndices;
public:
    DebugDraw(std::vector<float> vert, std::vector<unsigned int> incdic, const matrix4 projMat, vector3 color = {1, 0, 0});

    DebugDraw(std::vector<float> vert, const matrix4 projMat, vector3 color = {1, 0, 0});

    void Render(const matrix4 translationMat, const matrix4 viewMat);

    matrix4 translationMat;

    ~DebugDraw();
};
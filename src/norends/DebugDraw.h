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
    DebugDraw(std::vector<float> vert, std::vector<unsigned int> incdic, const Matrix<float, 4> projMat, Vector<float, 3> color = Vector<float, 3>{1, 0, 0});

    DebugDraw(std::vector<float> vert, const Matrix<float, 4> projMat, Vector<float, 3> color = Vector<float, 3>{1, 0, 0});

    void Render(const Matrix<float, 4> transformMatrix, const Matrix<float, 4> viewMat);

    Matrix<float, 4> transformMatrix;

    ~DebugDraw();
};
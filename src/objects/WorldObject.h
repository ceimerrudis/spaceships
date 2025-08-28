#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"

struct WorldObject {
public:
    Vector<float, 3> position;
    Vector<float, 3> right;
    Vector<float, 3> up;
    Vector<float, 3> forward;
    Matrix<float, 4> transformMatrix;

    WorldObject();

    void Move(Vector<float, 3> translate);

    void Move(float x, float y, float z);

    void Rotate(Vector<float, 3> axis, float angle);

    void UpdateTransformationMatrix();

    void Orthonormalize();

    Matrix<float, 4> GetRotMatrix();
};
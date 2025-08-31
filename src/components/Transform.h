#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"

struct Transform
{
    #if DEBUG
        bool initialized;
    #endif
    Vector<float, 3> position;
    Vector<float, 3> right;
    Vector<float, 3> up;
    Vector<float, 3> forward;
    Matrix<float, 4> transformMatrix;
};

void InitTransform(Transform& transform);

void Move(Transform& transform, float x, float y, float z);

inline void Move(Transform& transform, Vector<float, 3> translate){
    Move(transform, translate.data[0], translate.data[1], translate.data[2]);
}

void Rotate(Transform& transform, Vector<float, 3> axis, float angle);

void UpdateTransformationMatrix(Transform& transform);

Vector<float, 3> rodriguesRotate(const Vector<float, 3>& v, const Vector<float, 3>& k, double theta);

void Orthonormalize(Transform& transform);

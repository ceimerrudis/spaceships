#pragma once
#include "GlobalInclude.h"
#include "AdvancedMath.h"

struct WorldObject {
public:
    vector3 position;
    vector3 right;
    vector3 up;
    vector3 forward;
    matrix4 translationMat;

    WorldObject();

    void move(vector3 translate);

    void move(float x, float y, float z);

    void rotate(vector3 axis, float angle);

    void updateTranslationMat();

    void orthonormalize();

    matrix4 GetRotMatrix();
};
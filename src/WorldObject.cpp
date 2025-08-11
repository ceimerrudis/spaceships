#include "WorldObject.h"
#include <math.h>
#include <iostream>
#include <array>
#include "AdvancedMath.h"

WorldObject::WorldObject()
{
    right.data[0] = 0;
    right.data[1] = 0;
    right.data[2] = 1;
    up.data[0] = 0;
    up.data[1] = 1;
    up.data[2] = 0;
    forward.data[0] = 1;
    forward.data[1] = 0;
    forward.data[2] = 0;
    position = initV3();
    updateTranslationMat();
}

void WorldObject::move(vector3 translate){
    move(translate.data[0], translate.data[1], translate.data[2]);
}

void WorldObject::move(float x, float y, float z)
{
    position.data[0] = position.data[0] + x;
    position.data[1] = position.data[1] + y;
    position.data[2] = position.data[2] + z;
    updateTranslationMat();
}
void updateTranslationMat();
vector3 rodriguesRotate(const vector3& v, const vector3& k, double theta);
void WorldObject::rotate(vector3 axis, float angle)
{
    up = rodriguesRotate(up, axis, angle);
    right = rodriguesRotate(right, axis, angle);
    forward = rodriguesRotate(forward, axis, angle);
    updateTranslationMat();
}

void WorldObject::updateTranslationMat()
{
    translationMat(0, 0) = right.data[0];
    translationMat(0, 1) = up.data[0];
    translationMat(0, 2) = forward.data[0];
    translationMat(0, 3) = position.data[0];

    translationMat(1, 0) = right.data[1];
    translationMat(1, 1) = up.data[1];
    translationMat(1, 2) = forward.data[1];
    translationMat(1, 3) = position.data[1];

    translationMat(2, 0) = right.data[2];
    translationMat(2, 1) = up.data[2];
    translationMat(2, 2) = forward.data[2];
    translationMat(2, 3) = position.data[2];
    
    translationMat(3, 0) = 0.0f;
    translationMat(3, 1) = 0.0f;
    translationMat(3, 2) = 0.0f;
    translationMat(3, 3) = 1.0f;
}
vector3 aRotate(const vector3& p, const vector3& v, double a);
vector3 rodriguesRotate(const vector3& v, const vector3& k, double theta) {
    return aRotate(v, k, theta);
    vector3 k_cross_v = k * v;
    double k_dot_v = k % v;
    vector3 term1 = v * std::cos(theta);
    vector3 term2 = k_cross_v * std::sin(theta);
    vector3 term3 = k * (k_dot_v * (1 - std::cos(theta)));
    return term1 + term2 + term3;
}

vector3 aRotate(const vector3& p, const vector3& v, double a) {
    float ca = cos(a), sa = sin(a);
    float t = 1.0 - ca;
    float x = v.x(), y = v.y(), z = v.z();
    
    matrix3 r;
    std::array<float, 3> temp;
    temp = {ca + x*x*t, x*y*t - z*sa, x*z*t + y*sa};
    r.set_row(0, temp.data());
    temp = {x*y*t + z*sa, ca + y*y*t, y*z*t - x*sa};
    r.set_row(1, temp.data());
    temp = {z*x*t - y*sa, z*y*t + x*sa, ca + z*z*t};
    r.set_row(2, temp.data());
    
    return VecMultipliedByMatrix(p, r);
}

/*
void orthonormalize(Vec3 v1, Vec3 v2, Vec3 v3, Vec3& u1, Vec3& u2, Vec3& u3) {
    u1 = normalize(v1);

    Vec3 proj_u1_v2 = scale(u1, dot(v2, u1));
    Vec3 ortho_v2 = subtract(v2, proj_u1_v2);
    u2 = normalize(ortho_v2);

    Vec3 proj_u1_v3 = scale(u1, dot(v3, u1));
    Vec3 proj_u2_v3 = scale(u2, dot(v3, u2));
    Vec3 ortho_v3 = subtract(subtract(v3, proj_u1_v3), proj_u2_v3);
    u3 = normalize(ortho_v3);
}
*/
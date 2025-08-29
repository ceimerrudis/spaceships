#include "WorldObject.h"
#include <math.h>
#include <iostream>
#include <array>
#include "AdvancedMath.h"

WorldObject::WorldObject()
{
    right.x() = 0;
    right.y() = 0;
    right.z() = 1;
    up.x() = 0;
    up.y() = 1;
    up.z() = 0;
    forward.x() = 1;
    forward.y() = 0;
    forward.z() = 0;
    position.Init0();
    UpdateTransformationMatrix();
}

void WorldObject::Move(Vector<float, 3> translate){
    Move(translate.data[0], translate.data[1], translate.data[2]);
}

void WorldObject::Move(float x, float y, float z)
{
    position.data[0] = position.data[0] + x;
    position.data[1] = position.data[1] + y;
    position.data[2] = position.data[2] + z;
    UpdateTransformationMatrix();
}

Vector<float, 3> rodriguesRotate(const Vector<float, 3>& v, const Vector<float, 3>& k, double theta);

void WorldObject::Rotate(Vector<float, 3> axis, float angle)
{
    up = rodriguesRotate(up, axis, angle);
    right = rodriguesRotate(right, axis, angle);
    forward = rodriguesRotate(forward, axis, angle);
    UpdateTransformationMatrix();
}

void WorldObject::UpdateTransformationMatrix()
{
    /** 
    Forwardx Upx  Rightx   posx
    Forwardy Upy  Righty   posy
    Forwardz Upz  Rightz   posz
    0         0     0       1
    **/
    Orthonormalize();
    transformMatrix(0, 0) = forward.data[0];
    transformMatrix(0, 1) = up.data[0];
    transformMatrix(0, 2) = right.data[0];
    transformMatrix(0, 3) = position.data[0];

    transformMatrix(1, 0) = forward.data[1];
    transformMatrix(1, 1) = up.data[1];
    transformMatrix(1, 2) = right.data[1];
    transformMatrix(1, 3) = position.data[1];

    transformMatrix(2, 0) = forward.data[2];
    transformMatrix(2, 1) = up.data[2];
    transformMatrix(2, 2) = right.data[2];
    transformMatrix(2, 3) = position.data[2];
    
    transformMatrix(3, 0) = 0.0f;
    transformMatrix(3, 1) = 0.0f;
    transformMatrix(3, 2) = 0.0f;
    transformMatrix(3, 3) = 1.0f;
}
Vector<float, 3> aRotate(const Vector<float, 3>& p, const Vector<float, 3>& v, double a);
Vector<float, 3> rodriguesRotate(const Vector<float, 3>& v, const Vector<float, 3>& k, double theta) {
    return aRotate(v, k, theta);
    //Vector<float, 3> k_cross_v = k * v;
    //double k_dot_v = k % v;
    //Vector<float, 3> term1 = v * std::cos(theta);
    //Vector<float, 3> term2 = k_cross_v * std::sin(theta);
    //Vector<float, 3> term3 = k * (k_dot_v * (1 - std::cos(theta)));
    //return term1 + term2 + term3;
}

Vector<float, 3> aRotate(const Vector<float, 3>& p, const Vector<float, 3>& v, double a) {
    if(v.x() == 0 && v.y() == 0 && v.z() == 0) 
    {
        return p;
    }
    float ca = cos(a), sa = sin(a);
    float t = 1.0 - ca;
    float x = v.x(), y = v.y(), z = v.z();
    
    Matrix<float, 3> r;
    std::array<float, 3> temp;
    temp = {ca + x*x*t, x*y*t - z*sa, x*z*t + y*sa};
    r.SetRow(0, temp.data());
    temp = {x*y*t + z*sa, ca + y*y*t, y*z*t - x*sa};
    r.SetRow(1, temp.data());
    temp = {z*x*t - y*sa, z*y*t + x*sa, ca + z*z*t};
    r.SetRow(2, temp.data());

    return r * p;
}

void WorldObject::Orthonormalize() {
    right = right.Normalized();

    Vector<float, 3> proj_u1_v2 = right * (up % right);
    Vector<float, 3> ortho_v2 = up - proj_u1_v2;
    up = ortho_v2.Normalized();

    Vector<float, 3> proj_u1_v3 = right* (forward % right);
    Vector<float, 3> proj_u2_v3 = up * (forward % up);
    Vector<float, 3> ortho_v3 = forward - proj_u1_v3 - proj_u2_v3;
    forward = ortho_v3.Normalized();
}

Matrix<float, 4> WorldObject::GetRotMatrix()
{
    Matrix<float, 4> mat = transformMatrix;
    mat(0, 3) = 0;
    mat(1, 3) = 0;
    mat(2, 3) = 0;
    return mat;
}

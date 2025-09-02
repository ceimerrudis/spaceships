#include "Transform.h"
#include <array>
#include <math.h>

void Move(Transform& transform, float x, float y, float z)
{
    transform.position.data[0] = transform.position.data[0] + x;
    transform.position.data[1] = transform.position.data[1] + y;
    transform.position.data[2] = transform.position.data[2] + z;
    UpdateTransformationMatrix(transform);
}

void Rotate(Transform& transform, Vector<float, 3> axis, float angle)
{
    transform.up = rodriguesRotate(transform.up, axis, angle);
    transform.right = rodriguesRotate(transform.right, axis, angle);
    transform.forward = rodriguesRotate(transform.forward, axis, angle);
    UpdateTransformationMatrix(transform);
}

void LookAt(Transform& transform, Vector<float, 3> lookAt){
    Vector<float, 3> axis = (transform.forward * lookAt).Normalized();
    float angle = acosf(clamp(transform.forward % lookAt, -1.0f, 1.0f));
    Rotate(transform, axis, angle);
}

void UpdateTransformationMatrix(Transform& transform)
{
    /** 
    Forwardx Upx  Rightx   posx
    Forwardy Upy  Righty   posy
    Forwardz Upz  Rightz   posz
    0         0     0       1
    **/
    Orthonormalize(transform);
    transform.transformMatrix(0, 0) = transform.forward.data[0];
    transform.transformMatrix(0, 1) = transform.up.data[0];
    transform.transformMatrix(0, 2) = transform.right.data[0];
    transform.transformMatrix(0, 3) = transform.position.data[0];

    transform.transformMatrix(1, 0) = transform.forward.data[1];
    transform.transformMatrix(1, 1) = transform.up.data[1];
    transform.transformMatrix(1, 2) = transform.right.data[1];
    transform.transformMatrix(1, 3) = transform.position.data[1];

    transform.transformMatrix(2, 0) = transform.forward.data[2];
    transform.transformMatrix(2, 1) = transform.up.data[2];
    transform.transformMatrix(2, 2) = transform.right.data[2];
    transform.transformMatrix(2, 3) = transform.position.data[2];
    
    transform.transformMatrix(3, 0) = 0.0f;
    transform.transformMatrix(3, 1) = 0.0f;
    transform.transformMatrix(3, 2) = 0.0f;
    transform.transformMatrix(3, 3) = 1.0f;
}

Vector<float, 3> rodriguesRotate(const Vector<float, 3>& v, const Vector<float, 3>& k, double theta) {
    if(k.x() == 0 && k.y() == 0 && k.z() == 0) 
    {
        return v;
    }
    float ca = cos(theta), sa = sin(theta);
    float t = 1.0 - ca;
    float x = k.x(), y = k.y(), z = k.z();
    
    Matrix<float, 3> r;
    std::array<float, 3> temp;
    temp = {ca + x*x*t, x*y*t - z*sa, x*z*t + y*sa};
    r.SetRow(0, temp.data());
    temp = {x*y*t + z*sa, ca + y*y*t, y*z*t - x*sa};
    r.SetRow(1, temp.data());
    temp = {z*x*t - y*sa, z*y*t + x*sa, ca + z*z*t};
    r.SetRow(2, temp.data());

    return r * v;
}

void Orthonormalize(Transform& transform)
{
    transform.right = transform.right.Normalized();

    Vector<float, 3> proj_u1_v2 = transform.right * (transform.up % transform.right);
    Vector<float, 3> ortho_v2 = transform.up - proj_u1_v2;
    transform.up = ortho_v2.Normalized();

    Vector<float, 3> proj_u1_v3 = transform.right* (transform.forward % transform.right);
    Vector<float, 3> proj_u2_v3 = transform.up * (transform.forward % transform.up);
    Vector<float, 3> ortho_v3 = transform.forward - proj_u1_v3 - proj_u2_v3;
    transform.forward = ortho_v3.Normalized();
}

void InitTransform(Transform& transform)
{
    #if DEBUG
        transform.initialized = true;
    #endif
    transform.right.x() = 0;
    transform.right.y() = 0;
    transform.right.z() = 1;
    transform.up.x() = 0;
    transform.up.y() = 1;
    transform.up.z() = 0;
    transform.forward.x() = 1;
    transform.forward.y() = 0;
    transform.forward.z() = 0;
    transform.position.Init0();
    UpdateTransformationMatrix(transform);
}

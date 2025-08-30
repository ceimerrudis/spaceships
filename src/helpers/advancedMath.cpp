#include "advancedMath.h"
#include "Matrix.h"
#include "Vector.h"
#include <math.h>
#include <algorithm>

const float TO_RAD = M_PI / 180.0f;

Matrix<float, 4>  CreateProjectionMatrix(int width, int height, float size)
{
    Matrix<float, 4> ProjectionMatrix;
    ProjectionMatrix.Init0();
    float znear =  0.1f;
    float zfar = 10000.0f;
    float aspect = float(width) / float(height);
    float zCoef = zfar/(zfar-znear);

    float fovY = 2.0f * atanf(height / (2.0f * size));
    fovY = std::clamp(fovY, 1.0f * TO_RAD, 170.0f * TO_RAD); 
    float t = tanf(fovY * 0.5f);

    //*
    //float fov = 170;
    //float s = 1.0f/(std::tan(fov/2 * TO_RAD));
    ProjectionMatrix(0, 0) = 1 / (t * aspect);
    ProjectionMatrix(1, 1) = 1 / t;
    ProjectionMatrix(2, 2) = -(zfar + znear) / (zfar - znear); 
    ProjectionMatrix(3, 2) =  -1.0f;
    ProjectionMatrix(2, 3) = -2.0f * znear * zCoef;
    //*/
    return ProjectionMatrix;
}

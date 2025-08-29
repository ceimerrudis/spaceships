#include "advancedMath.h"
#include "Matrix.h"
#include "Vector.h"

Matrix<float, 4>  CreateProjectionMatrix()
{
    Matrix<float, 4> ProjectionMatrix;
    float fov = 120;
    float s = 1.0f/(std::tan((fov/2) * (M_PI/180.0f)));
    ProjectionMatrix.Init0();
    ProjectionMatrix(0, 0) = s;
    ProjectionMatrix(1, 1) = s;
    float zfar = 1000.0f, znear =  0.01f;
    float zCoef = zfar/(zfar-znear);
    ProjectionMatrix(2, 2) = -zCoef;
    ProjectionMatrix(2, 3) = -zCoef*znear;
    ProjectionMatrix(3, 2) = -1;

    return ProjectionMatrix;
}

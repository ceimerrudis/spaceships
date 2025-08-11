#include "advancedMath.h"

void matrix3::set_row(int row, float* threeFloats) {
    int base = row * 3;
    data[base + 0] = threeFloats[0];
    data[base + 1] = threeFloats[1];
    data[base + 2] = threeFloats[2];
}

void matrix4::set_row(int row, float* fourFloats) {
    int base = row * 4;
    data[base + 0] = fourFloats[0];
    data[base + 1] = fourFloats[1];
    data[base + 2] = fourFloats[2];
    data[base + 3] = fourFloats[3];
}

vector3& vector3::operator =(const vector3& a)
{
    data[0] = a.data[0];
    data[1] = a.data[1];
    data[2] = a.data[2];
    return *this;
}

vector3 vector3::operator +(const vector3& a) const
{
    vector3 b;
    b.data[0] = data[0] + a.data[0];
    b.data[1] = data[1] + a.data[1];
    b.data[2] = data[2] + a.data[2];
    return b;
}

const vector3 vector3::operator *(const vector3& a) const
{
    vector3 b;
    b.data[0] = data[1] * a.data[2] - data[2] * a.data[1];
    b.data[1] = data[2] * a.data[0] - data[0] * a.data[2];
    b.data[2] = data[0] * a.data[1] - data[1] * a.data[0];
    return b;
}

vector3 vector3::operator *(const float& a) const
{
    vector3 b;
    b.data[0] = data[0] * a;
    b.data[1] = data[1] * a;
    b.data[2] = data[2] * a;
    return b;
}

vector3 vector3::operator *(const int& a) const
{
    vector3 b;
    b.data[0] = data[0] * a;
    b.data[1] = data[1] * a;
    b.data[2] = data[2] * a;
    return b;
}

vector3 vector3::operator *(const double& a) const
{
    vector3 b;
    b.data[0] = data[0] * a;
    b.data[1] = data[1] * a;
    b.data[2] = data[2] * a;
    return b;
}

float vector3::operator %(const vector3& a) const
{
    return  data[0]*a.data[0] +
            data[1]*a.data[1] +
            data[2]*a.data[2];
}


vector2& vector2::operator =(const vector2& a)
{
    data[0] = a.data[0];
    data[1] = a.data[1];
    return *this;
}

vector2 vector2::operator +(const vector2& a) const
{
    vector2 b;
    b.data[0] = data[0] + a.data[0];
    b.data[1] = data[1] + a.data[1];
    return b;
}

vector2 vector2::operator *(const float& a) const
{
    vector2 b;
    b.data[0] = data[0] * a;
    b.data[1] = data[1] * a;
    return b;
}

vector2 vector2::operator *(const int& a) const
{
    vector2 b;
    b.data[0] = data[0] * a;
    b.data[1] = data[1] * a;
    return b;
}

vector2 vector2::operator *(const double& a) const
{
    vector2 b;
    b.data[0] = data[0] * a;
    b.data[1] = data[1] * a;
    return b;
}

float vector2::operator %(const vector2& a) const
{
    return  data[0]*a.data[0] +
            data[1]*a.data[1];
}

vector3 initV3(){
    vector3 vec;
    for(int i = 0; i < 3; i++)
    {
        vec.data[i]  = 0;
    }
    return vec;
}
vector4 initV(){
    vector4 vec;
    for(int i = 0; i < 4; i++)
    {
        vec.data[i]  = 0;
    }
    return vec;
}
matrix4 initM(){
    matrix4 mat;
    for(int i = 0; i < 16; i++)
    {
        mat.data[i] = 0;
    }
    return mat;
}

matrix4 Identity()
{
    matrix4 mat;
    mat = initM();
    mat.data[0 + (0*4)] = 1;
    mat.data[1 + (1*4)] = 1;
    mat.data[2 + (2*4)] = 1;
    mat.data[3 + (3*4)] = 1;
    return mat;
}

matrix4 MatrixMultipliedByMatrix(matrix4 matA, matrix4 matB) {
    matrix4 result;
    result = initM();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result.data[i + (j*4)] = result.data[i + (j*4)] + matA.data[i + (k*4)] * matB.data[k + (j*4)];
            }
        }
    }
    return result;
}

vector4 VecMultipliedByMatrix(vector4 vec, matrix4 mat)
{
    vector4 resultVector;
    resultVector = initV();
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            resultVector.data[i] = resultVector.data[i] + vec.data[j] * mat(i, j);
        }
    }
    return resultVector;
}


vector3 VecMultipliedByMatrix(vector3 vec, matrix3 mat)
{
    vector3 resultVector;
    resultVector.data[0] = 0;
    resultVector.data[1] = 0;
    resultVector.data[2] = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            resultVector.data[i] = resultVector.data[i] + vec.data[j] * mat(i, j);
        }
    }
    return resultVector;
}

//2x2 matricas determinants
float det(float r1c1, float r1c2,  float r2c1, float r2c2)
{
    return (r1c1 * r2c2) - (r1c2 * r2c1);
}

void copyMat(float* src, float* target){
    for(int i = 0; i < 16; i++)
    {
        target[i] = src[i];
    }
}

matrix4  CreateProjectionMatrix()
{
    matrix4 ProjectionMatrix;
    float fov = 120;
    float s = 1.0f/(std::tan((fov/2) * (M_PI/180.0f)));
    ProjectionMatrix = initM();
    ProjectionMatrix.data[0 + (0*4)] = s;
    ProjectionMatrix.data[1 + (1*4)] = s;
    float zfar = 1000.0f, znear =  0.01f;
    float zCoef = zfar/(zfar-znear);
    ProjectionMatrix.data[2 + (2*4)] = -zCoef;
    ProjectionMatrix.data[3 + (2*4)] = -zCoef*znear;
    ProjectionMatrix.data[2 + (3*4)] = -1;

    return ProjectionMatrix;
}

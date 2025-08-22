#include "advancedMath.h"
#include <Eigen/Dense>

matrix4 matrix4::Inverse(){
    Eigen::Matrix4f result;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            //if(row < 3 && col == 2)
            //{
            //    result(row, col) = -(*this)(row, col);
            //}
            //else
            //{
                result(row, col) = (*this)(row, col);
            //}
        }
    }
    
    Eigen::Matrix4f inv = result.inverse();

    matrix4 m;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            m(row, col) = inv(row, col);
        }
    }
    return m;
}


const matrix3 matrix3::Inverse(){
    Eigen::Matrix3f result;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            result(row, col) = (*this)(row, col);
        }
    }
    
    Eigen::Matrix3f inv = result.inverse();

    matrix3 m;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            m(row, col) = inv(row, col);
        }
    }
    return m;
}

matrix4 matrix4::JustTranslationAndScale()
{
    matrix4 mat;
    for (int i = 0; i < 4; ++i) {
        mat(i, 4) = (*this)(i, 4);
        mat(4, i) = (*this)(4, i);
    }
    mat(0, 0) = 1;
    mat(1, 1) = 1;
    mat(2, 2) = 1;
    return mat;
}

void matrix3::set_row(int row, float* threeFloats) {
    int base = row * 3;
    data[base + 0] = threeFloats[0];
    data[base + 1] = threeFloats[1];
    data[base + 2] = threeFloats[2];
}

matrix3 matrix3::transpose() const
{
    matrix3 res;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            res(row, col) = (*this)(col, row);
        }
    }
    return res;
}

vector3 matrix3::operator *(const vector3& a) const
{
    vector3 result;
    result.x() = (*this)(0, 0) * a.x() + (*this)(0, 1) * a.y() + (*this)(0, 2) * a.z();
    result.y() = (*this)(1, 0) * a.x() + (*this)(1, 1) * a.y() + (*this)(1, 2) * a.z();
    result.z() = (*this)(2, 0) * a.x() + (*this)(2, 1) * a.y() + (*this)(2, 2) * a.z();
    return result;
}

matrix3& matrix3::operator =(const matrix4& a)
{
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            (*this)(row, col) = a(row, col);
        }
    }
    return (*this);
}

vector3 matrix3::getCol(int Col) const
{
    vector3 res;
    res.x() = (*this)(0, Col);
    res.y() = (*this)(1, Col);
    res.z() = (*this)(2, Col);
    return res;
}

void matrix4::set_row(int row, float* fourFloats) {
    int base = row * 4;
    data[base + 0] = fourFloats[0];
    data[base + 1] = fourFloats[1];
    data[base + 2] = fourFloats[2];
    data[base + 3] = fourFloats[3];
}

vector4 vector4::Normalized()
{
    float len = sqrt(x() * x() + y() * y() + z() * z() + w() * w());
    if (len == 0.0f)
        return vector4{0, 0, 0};

    return vector4{x() / len, y() / len, z() / len, w() / len};
}

float vector3::magnitude()
{
    return sqrt(x()*x()+y()*y()+z()*z());
}

std::string vector3::ToString()
{
    std::string res;
    res = "";
    res += std::to_string(x());
    res += ", ";
    res += std::to_string(y());
    res += ", ";
    res += std::to_string(z());
    return res;
}   

const vector3 vector3::Normalized()
{
    float len = sqrt(x() * x() + y() * y() + z() * z());

    if (len == 0.0f)
        return vector3{0, 0, 0};

    return vector3{x() / len, y() / len, z() / len};
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

vector3 vector3::operator -(const vector3& a) const
{
    vector3 b;
    b.data[0] = data[0] - a.data[0];
    b.data[1] = data[1] - a.data[1];
    b.data[2] = data[2] - a.data[2];
    return b;
}

//cross product
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

//dot prod
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

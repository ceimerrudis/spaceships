#pragma once
#include "GlobalInclude.h"
#include <math.h>

struct matrix4
{
    float data[16];

    inline float& operator()(int row, int col) {
        return data[row * 4 + col];
    }

    inline float operator()(int row, int col) const {
        return data[row * 4 + col];
    }

    void set_row(int row, float* fourFloats);
};

struct matrix3
{
    float data[9];

    inline float& operator()(int row, int col) {
        return data[row * 3 + col];
    }

    inline float operator()(int row, int col) const {
        return data[row * 3 + col];
    }

    void set_row(int row, float* threeFloats);
};

struct vector4
{
    float data[4];
    inline float x() const { return data[0]; }
    inline float y() const { return data[1]; }
    inline float z() const { return data[2]; }
    inline float w() const { return data[3]; }

    inline float& x() { return data[0]; }
    inline float& y() { return data[1]; }
    inline float& z() { return data[2]; }
    inline float& w() { return data[3]; }
};

struct vector3
{
    float data[3];

    inline float x() const { return data[0]; }
    inline float y() const { return data[1]; }
    inline float z() const { return data[2]; }

    inline float& x() { return data[0]; }
    inline float& y() { return data[1]; }
    inline float& z() { return data[2]; }
    
    vector3& operator =(const vector3& a);

    vector3 operator +(const vector3& a) const;

    const vector3 operator *(const vector3& a) const;

    vector3 operator *(const float& a) const;

    vector3 operator *(const int& a) const;

    vector3 operator *(const double& a) const;

    float operator %(const vector3& a) const;
};

struct vector2
{
    float data[2];

    inline float x() const { return data[0]; }
    inline float y() const { return data[1]; }

    inline float& x() { return data[0]; }
    inline float& y() { return data[1]; }
    
    vector2& operator =(const vector2& a);

    vector2 operator +(const vector2& a) const;

    vector2 operator *(const float& a) const;

    vector2 operator *(const int& a) const;

    vector2 operator *(const double& a) const;

    float operator %(const vector2& a) const;
};

struct vector2i
{
    int data[2];

    inline int x() const { return data[0]; }
    inline int y() const { return data[1]; }

    inline int& x() { return data[0]; }
    inline int& y() { return data[1]; }
};

matrix4  CreateProjectionMatrix();

vector3 initV3();

vector4 initV();

matrix4 initM();

matrix4 Identity();

matrix4 MatrixMultipliedByMatrix(matrix4 matA, matrix4 matB);
vector4 VecMultipliedByMatrix(vector4 vec, matrix4 mat);
vector3 VecMultipliedByMatrix(vector3 vec, matrix3 mat);

//2x2 matricas determinants
float det(float r1c1, float r1c2,  float r2c1, float r2c2);

void copyMat(float* src, float* target);

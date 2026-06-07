#pragma once
#include <string>

namespace cat 
{
template<typename T, unsigned int N>
struct Vector
{
    T data[N];

    inline T x() const { return data[0]; }
    inline T y() const { return data[1]; }
    inline T z() const { return data[2]; }
    inline T w() const { return data[3]; }

    inline T& x() { return data[0]; }
    inline T& y() { return data[1]; }
    inline T& z() { return data[2]; }
    inline T& w() { return data[3]; }

    void Init0();
    
    float Magnitude() const;

    Vector<T, N> Normalized() const;

    //assign op
    Vector<T, N>& operator =(const Vector<T, N>& a);

    //addition
    Vector<T, N> operator +(const Vector<T, N>& a) const;

    //subtraction
    Vector<T, N> operator -(const Vector<T, N>& a) const;

    //Cross product
    const Vector<T, N> operator *(const Vector<T, N>& a) const;

    //Scalar multiplication
    Vector<T, N> operator *(const float& a) const;

    //Scalar multiplication
    Vector<T, N> operator *(const int& a) const;

    //Scalar multiplication
    Vector<T, N> operator *(const double& a) const;

    //Dot product
    float operator % (const Vector<T, N>& a) const;

    std::string ToString() const;
};
template<typename T, unsigned int N>
struct ComplexVector
{
    T data[N];

    inline T x() const { return data[0]; }
    inline T y() const { return data[1]; }
    inline T z() const { return data[2]; }
    inline T w() const { return data[3]; }

    inline T& x() { return data[0]; }
    inline T& y() { return data[1]; }
    inline T& z() { return data[2]; }
    inline T& w() { return data[3]; }

    //assign op
    ComplexVector<T, N>& operator =(const ComplexVector<T, N>& a);
};
}

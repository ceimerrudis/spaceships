#include "Vector.h"
#include <Math.h>

template class Vector<float, 3>;
template class Vector<float, 4>;
template class Vector<float, 2>;
template class Vector<int, 2>;

template<typename T, unsigned int N>
void Vector<T, N>::Init0()
{
    int n = N;
    for (int i = 0; i < n; i++)
    {
        data[i] = 0;
    }
}

template<typename T, unsigned int N>
float Vector<T, N>::Magnitude() const
{
    float squareSums = 0;
    for (int i = 0; i < N; i++)
    {
        squareSums = squareSums + (data[i] * data[i]);
    }
    return sqrt(squareSums);
}

template<typename T, unsigned int N>
Vector<T, N> Vector<T, N>::Normalized() const
{
    float len = Magnitude();
    Vector<T, N> result;
    if (len == 0.0f)
    {
        result.Init0();
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            result.data[i] = data[i] / len;
        }
    }

    return result;
}

//assign op
template<typename T, unsigned int N>
Vector<T, N>& Vector<T, N>::operator =(const Vector<T, N>& a)
{
    for (int i = 0; i < N; i++)
    {
        data[i] = a.data[i];
    }
    return *this;
}

//addition
template<typename T, unsigned int N>
Vector<T, N> Vector<T, N>::operator +(const Vector<T, N>& a) const
{
    Vector<T, N> result;
    for (int i = 0; i < N; i++)
    {
        result.data[i] = data[i] + a.data[i];
    }
    return result;
}

//subtraction
template<typename T, unsigned int N>
Vector<T, N> Vector<T, N>::operator -(const Vector<T, N>& a) const
{
    Vector<T, N> result;
    for (int i = 0; i < N; i++)
    {
        result.data[i] = data[i] - a.data[i];
    }
    return result;
}

//Cross product
template<typename T, unsigned int N>
const Vector<T, N> Vector<T, N>::operator *(const Vector<T, N>& a) const
{
    #if DEBUG 
        if(N != 3) 
        {
            error("Cross product only exists for 3 dimensions.");
        }
    #endif
    Vector<T, N> result;
    result.data[0] = data[1] * a.data[2] - data[2] * a.data[1];
    result.data[1] = data[2] * a.data[0] - data[0] * a.data[2];
    result.data[2] = data[0] * a.data[1] - data[1] * a.data[0];    
    return result;
}

//Scalar multiplication
template<typename T, unsigned int N>
Vector<T, N> Vector<T, N>::operator *(const float& a) const
{
    Vector<T, N> result;
    for (int i = 0; i < N; i++)
    {
        result.data[i] = data[i] * a;
    }
    return result;
}

//Scalar multiplication
template<typename T, unsigned int N>
Vector<T, N> Vector<T, N>::operator *(const int& a) const
{
    Vector<T, N> result;
    for (int i = 0; i < N; i++)
    {
        result.data[i] = data[i] * a;
    }
    return result;
}

//Scalar multiplication
template<typename T, unsigned int N>
Vector<T, N> Vector<T, N>::operator *(const double& a) const
{
    Vector<T, N> result;
    for (int i = 0; i < N; i++)
    {
        result.data[i] = data[i] * a;
    }
    return result;
}

//Dot product
template<typename T, unsigned int N>
float Vector<T, N>::operator % (const Vector<T, N>& a) const
{
    float result = 0;
    for (int i = 0; i < N; i++)
    {
        result = result + (data[i] * a.data[i]);
    }
    return result;
}

template<typename T, unsigned int N>
std::string Vector<T, N>::ToString() const
{
    std::string res;
    res = "";
    for (int i = 0; i < N; i++)
    {
        res += std::to_string(data[i]);
        res += ", ";
    }
    return res;
}
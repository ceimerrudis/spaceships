#pragma once
#include "cat/Vector.h"
#include "cat/Logger.h"
#include <string>

namespace cat 
{
//Strictly square matrix row major
template<typename T, unsigned int N>
struct Matrix
{
    T data[N*N];

    inline T& operator()(int row, int col) {
        return data[row * N + col];
    }

    inline T operator()(int row, int col) const {
        return data[row * N + col];
    }

    void Init0();

    void SetRow(int row, T* rowData);

    inline float Determinant() const
    {
        if constexpr (N == 1)
        {
            return (*this)(0,0);
        }
        // N == 2
        else if constexpr (N == 2)
        {
            return (*this)(0,0) * (*this)(1,1) -
                (*this)(0,1) * (*this)(1,0);
        }
        // N == 3
        else if constexpr (N == 3)
        {
            return
                (*this)(0,0) * ((*this)(1,1) * (*this)(2,2) - (*this)(1,2) * (*this)(2,1)) -
                (*this)(0,1) * ((*this)(1,0) * (*this)(2,2) - (*this)(1,2) * (*this)(2,0)) +
                (*this)(0,2) * ((*this)(1,0) * (*this)(2,1) - (*this)(1,1) * (*this)(2,0));
        }
        // N == 4
        else if constexpr (N == 4)
        {
            T det =
                (*this)(0,0) * (
                    (*this)(1,1) * ((*this)(2,2) * (*this)(3,3) - (*this)(2,3) * (*this)(3,2)) -
                    (*this)(1,2) * ((*this)(2,1) * (*this)(3,3) - (*this)(2,3) * (*this)(3,1)) +
                    (*this)(1,3) * ((*this)(2,1) * (*this)(3,2) - (*this)(2,2) * (*this)(3,1))
                )
            - (*this)(0,1) * (
                    (*this)(1,0) * ((*this)(2,2) * (*this)(3,3) - (*this)(2,3) * (*this)(3,2)) -
                    (*this)(1,2) * ((*this)(2,0) * (*this)(3,3) - (*this)(2,3) * (*this)(3,0)) +
                    (*this)(1,3) * ((*this)(2,0) * (*this)(3,2) - (*this)(2,2) * (*this)(3,0))
                )
            + (*this)(0,2) * (
                    (*this)(1,0) * ((*this)(2,1) * (*this)(3,3) - (*this)(2,3) * (*this)(3,1)) -
                    (*this)(1,1) * ((*this)(2,0) * (*this)(3,3) - (*this)(2,3) * (*this)(3,0)) +
                    (*this)(1,3) * ((*this)(2,0) * (*this)(3,1) - (*this)(2,1) * (*this)(3,0))
                )
            - (*this)(0,3) * (
                    (*this)(1,0) * ((*this)(2,1) * (*this)(3,2) - (*this)(2,2) * (*this)(3,1)) -
                    (*this)(1,1) * ((*this)(2,0) * (*this)(3,2) - (*this)(2,2) * (*this)(3,0)) +
                    (*this)(1,2) * ((*this)(2,0) * (*this)(3,1) - (*this)(2,1) * (*this)(3,0))
                );

            return det;
        }
        else
        {
            error("Determinant not implemented for theese dimensions.");
        }
    }

    Matrix<T, N-1> ReduceDimensions() const;

    Matrix<T, N-1> ReduceDimensions(int rowToIgnore, int colToIgnore) const;

    Matrix<T, N> Inverse() const;

    Vector<T, N> GetCol(int Col) const;

    Matrix<T, N> Transpose() const;

    Matrix<T, N>& operator =(const Matrix<T,N> a);

    //Assumes vector is column vector
    Vector<T, N> operator *(const Vector<T, N>& a) const;

    Matrix<T, N> operator *(const Matrix<T, N>& a) const;

    static Matrix<T, N> Identity();

    std::string ToString() const;
};
}

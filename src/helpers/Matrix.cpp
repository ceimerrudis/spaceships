#include "Matrix.h"
#include <math.h>
#include <sstream>
#include <iomanip>

template class Matrix<float, 2>;
template class Matrix<float, 3>;
template class Matrix<float, 4>;

template<typename T, unsigned int N>
void Matrix<T, N>::SetRow(int row, T* rowData)
{
    for (int i = 0; i < N; i++) 
    {
        (*this)(row, i) = rowData[i];
    }
}

template<typename T, unsigned int N>
Matrix<T, N-1> Matrix<T, N>::ReduceDimensions() const
{
    int dimensionCount = N - 1;
    Matrix<T, N - 1> result;
    for (int i = 0; i < dimensionCount; i++)
    {
        for (int j = 0; j < dimensionCount; j++) 
        {
            result(i, j) = (*this)(i, j);
        }
    }
    return result;
}

template<typename T, unsigned int N>
Matrix<T, N-1> Matrix<T, N>::ReduceDimensions(int rowToIgnore, int colToIgnore) const
{ 
    int dimensionCount = N - 1;
    Matrix<T, N - 1> result;
    int counter = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) 
        {   
            if(rowToIgnore != i && colToIgnore != j)
            {
                result.data[counter] = (*this)(i, j);
                counter++;
            }
        }
    }
    return result;
}

template<typename T, unsigned int N>
Matrix<T, N> Matrix<T, N>::Inverse() const
{
    //Possibe optimizatioon look into hard coded formulas
    Matrix<T, N> inverse;
    float det = Determinant();
    if(std::abs(det) < 0.000001)
    {
        inverse = *this;
        return Matrix<T, N>::Identity();    
    }

    det = 1 / det;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            inverse(j, i) = ((i+j)%2 ? -1 : 1) * ReduceDimensions(i, j).Determinant() * det;
        }    
    }
    
    return inverse;
}

template<typename T, unsigned int N>
Vector<T, N> Matrix<T, N>::GetCol(int col) const
{
    Vector<T, N> result;
    for (int i = 0; i < N; i++) 
    {
        result.data[i] = (*this)(i, col);
    }
    return result;
}

template<typename T, unsigned int N>
Matrix<T, N> Matrix<T, N>::Transpose() const
{
    Matrix<T, N> result;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            result(row, col) = (*this)(col, row);
        }
    }
    return result;
}

template<typename T, unsigned int N>
Matrix<T, N>& Matrix<T, N>::operator =(const Matrix<T,N> a)
{
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            (*this)(row, col) = a(row, col);
        }
    }
    return (*this);
}

//Assumes vector is column vector
template<typename T, unsigned int N>
Vector<T, N> Matrix<T, N>::operator *(const Vector<T, N>& a) const
{
    Vector<T, N> result;
    T sum;
    for (int i = 0; i < N; i++) {
        sum = 0;
        for (int j = 0; j < N; j++) {
            sum = sum + (*this)(i, j) * a.data[j];
        }
        result.data[i] = sum;
    }
    return result;
}    

template<typename T, unsigned int N>
Matrix<T, N> Matrix<T, N>::operator *(const Matrix<T, N>& a) const
{   
    Matrix<T, N> result;
    result.Init0();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                result(i, j) = result(i, j) + (*this)(i, k) * a(k, j);
            }
        }
    }
    return result;
}

template<typename T, unsigned int N>
void Matrix<T, N>::Init0()
{
    int n = N*N;
    for (int i = 0; i < n; i++)
    {
        data[i] = 0;
    }
}

template<typename T, unsigned int N>
Matrix<T, N> Matrix<T, N>::Identity()
{
    Matrix<T, N> mat;
    mat.Init0();
    for (int i = 0; i < N; i++)
    {
        mat(i, i) = 1;
    }
    return mat;
}

template<typename T, unsigned int N>
std::string Matrix<T, N>::ToString() const
{
    std::ostringstream oss;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::ostringstream cell;
            cell << (*this)(i, j);
            std::string cellStr = cell.str();

            if (cellStr.length() > 10)
                cellStr = cellStr.substr(0, 10);

            oss << " " << std::setw(12) << std::left << cellStr << " | ";
        }
        oss << '\n';
    }
    return oss.str();
}
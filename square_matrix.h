#ifndef SQUARE_MATRIX_H_INCLUDED
#define SQUARE_MATRIX_H_INCLUDED
#include "matrix.h"

//inherits from matrix
class SquareMatrix : public Matrix
{
    public:
        SquareMatrix();
        SquareMatrix(int);
        SquareMatrix(const Matrix&);
        SquareMatrix operator =(Matrix&);

        double determinant();
        SquareMatrix cofactor();
        SquareMatrix adjoint();
        SquareMatrix inverse();
        SquareMatrix transpose();

        void toeplitzDecomposition();
        void operations();
};

#endif // SQUARE_MATRIX_H_INCLUDED

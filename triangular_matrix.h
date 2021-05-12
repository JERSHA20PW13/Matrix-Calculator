#ifndef TRIANGULAR_MATRIX_H_INCLUDED
#define TRIANGULAR_MATRIX_H_INCLUDED
#include "square_matrix.h"

class TriangularMatrix : virtual public SquareMatrix
{
    public:
        TriangularMatrix();
        TriangularMatrix(int);
        double determinant();
        TriangularMatrix(const Matrix&);
        TriangularMatrix operator =(Matrix&);

        void operations();
        void editMatrix();
};

#endif // TRIANGULAR_MATRIX_H_INCLUDED

#ifndef DIAGONAL_MATRIX_H_INCLUDED
#define DIAGONAL_MATRIX_H_INCLUDED
#include "triangular_matrix.h"
#include "symmetric_matrix.h"

class DiagonalMatrix : public SymmetricMatrix, public TriangularMatrix
{
    public:
        DiagonalMatrix();
        DiagonalMatrix(int);
        DiagonalMatrix inverse();
        DiagonalMatrix(const Matrix&);
        DiagonalMatrix operator =(Matrix&);

        void operations();
        void editMatrix();

};

#endif // DIAGONAL_MATRIX_H_INCLUDED

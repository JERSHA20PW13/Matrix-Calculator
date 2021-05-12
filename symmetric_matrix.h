#ifndef SYMMETRIC_MATRIX_H_INCLUDED
#define SYMMETRIC_MATRIX_H_INCLUDED
#include "square_matrix.h"

class SymmetricMatrix : virtual public SquareMatrix
{
    public:
        SymmetricMatrix();
        SymmetricMatrix(int);
        SymmetricMatrix transpose();
        SymmetricMatrix(const Matrix&);
        SymmetricMatrix operator =(Matrix&);

        void operations();
        void editMatrix();
};

#endif // SYMMETRIC_MATRIX_H_INCLUDED

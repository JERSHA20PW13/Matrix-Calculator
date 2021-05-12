#include <iostream>
#include <cmath>
#include <conio.h>
#include "symmetric_matrix.h"

using namespace std;

SymmetricMatrix :: SymmetricMatrix() : SquareMatrix()
{

}

SymmetricMatrix :: SymmetricMatrix(int n) : SquareMatrix(n)
{

}

SymmetricMatrix::SymmetricMatrix(const Matrix& m)
{
    row = m.getRow();
    col = m.getColumn();
    pp = new double *[row];
    for(int i=0; i<row; i++)
        pp[i] = new double [col];

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            pp[i][j] = m.getElement(i, j);
}

SymmetricMatrix SymmetricMatrix::operator =(Matrix& m)
{
    row = m.getRow();
    col = m.getColumn();
    pp = new double *[row];
    for(int i=0; i<row; i++)
        pp[i] = new double [col];

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            pp[i][j] = m.getElement(i, j);
    return *this;
}

SymmetricMatrix SymmetricMatrix :: transpose()
{
    return *this;
}

void SymmetricMatrix :: editMatrix()
{
    double **temp_pp;
    temp_pp = new double *[row];
    for(int i=0; i<row; i++)
        temp_pp[i] = new double [col];

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            temp_pp[i][j] = pp[i][j];

    Matrix :: editMatrix();

    if(checkSymmetric())
        return;
    else
    {
        for(int i=0; i<row; i++)
            for(int j=0; j<col; j++)
                pp[i][j] = temp_pp[i][j];
        delete temp_pp;
        cout << "\nEdited matrix is not symmetric matrix..." << endl;
        return;
    }
}

void SymmetricMatrix::operations()
{
    int x=1, choice;
    while(x)
    {
        cout << "_  _ ____ ___ ____ _ _  _    ____ ____ _    ____ _  _ _    ____ ___ ____ ____    "
"\n|\\/| |__|  |  |__/ |  \\/     |    |__| |    |    |  | |    |__|  |  |  | |__/   "
"\n|  | |  |  |  |  \\ | _/\\_    |___ |  | |___ |___ |__| |___ |  |  |  |__| |  \\    ";
        cout << endl << endl;
        display();
        cout << "\t\tAvailable operations: " << endl;
        cout << "\t\t\t1. Add\n\t\t\t2. Subtract\n\t\t\t3. Scalar Multiplication\n\t\t\t4. Multiplication\n\t\t\t5. Transpose\n\t\t\t6. Edit Matrix\n\t\t\t7. Determinant\n\t\t\t8. Cofactor Matrix\n\t\t\t9. Adjoint Matrix\n\t\t\t10. Inverse Matrix\n\t\t\t11. Toeplitz Decomposition\n\t\t\t12. Sparse matrix to triplet notation\n\t\t\t13. Back" << endl;
        cout << "\t\tEnter your choice: ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
            case 1:
            {
                Matrix temp(row, col);
                cout << "The order of the matrix must be " << row << " x " << col << endl;
                temp.read();
                temp = *this + temp;
                cout << "RESULT: " << endl;
                temp.display();
                break;
            }
            case 2:
            {
                Matrix temp(row, col);
                cout << "The order of the matrix must be " << row << " x " << col << endl;
                temp.read();
                temp = *this - temp;
                cout << "RESULT: " << endl;
                temp.display();
                break;
            }
            case 3:
            {
                Matrix temp(row, col);
                double n;
                cout << "Enter a scalar to multiply: ";
                cin >> n;
                temp = scalarMultiplication(n);
                cout << "RESULT: " << endl;
                temp.display();
                break;
            }
            case 4:
            {
                int n;
                cout << "The order of the matrix must be " << col << " x " << "?" << endl;
                cout << "Column: ";
                cin >> n;
                Matrix temp(col, n);
                temp.read();
                temp = *this * temp;
                cout << "RESULT: " << endl;
                temp.display();
                break;
            }
            case 5:
            {
                SymmetricMatrix temp(row);
                temp = transpose();
                cout << "TRANSPOSE: " << endl;
                temp.display();
                break;
            }
            case 6:
            {
                editMatrix();
                cout << "NEW MATRIX:" << endl;
                display();
                break;
            }
            case 7:
            {
                double d;
                d = determinant();
                cout << "DETERMINANT: " << d <<endl;
                break;
            }
            case 8:
            {
                SquareMatrix r(row);
                r = cofactor();
                cout << "COFACTOR: " << endl;
                r.display();
                break;
            }
            case 9:
            {
                SquareMatrix r(row);
                r = adjoint();
                cout << "ADJOINT: " << endl;
                r.display();
                break;
            }
            case 10:
            {
                SquareMatrix r(row);
                r = inverse();
                cout << "NVERSE: " << endl;
                r.display();
                break;
            }
            case 11:
            {
                cout << "TOEPLITZ DECOMPOSITION" << endl << endl;
                toeplitzDecomposition();
                break;
            }
            case 12:
            {
                Matrix triplet = tripletNotation();
                cout << "TRIPLET NOTATION" << endl;
                triplet.display();
                break;
            }
            case 13:
            {
                x=0;
                break;
            }
            default:
            {
                cout << "INVALID CHOICE!" << endl;
            }
        }
        cout << "\n\n\n\nPress any key to continue..." << endl;
        getch();
        system("CLS");

    }
}


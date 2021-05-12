#include <iostream>
#include <cmath>
#include <conio.h>
#include "square_matrix.h"

using namespace std;

SquareMatrix::SquareMatrix(): Matrix()
{

}

SquareMatrix::SquareMatrix(int n) : Matrix(n, n)
{

}

SquareMatrix::SquareMatrix(const Matrix& m)
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

SquareMatrix SquareMatrix::operator =(Matrix& m)
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

double SquareMatrix::determinant()
{
    double det=0;
    SquareMatrix temp(row-1);
    int tempi, tempj;
    if (row==1) return pp[0][0];
    if (row==2) return (pp[0][0] * pp[1][1]) - (pp[0][1] * pp[1][0]);
    else
    {
        for(int x=0; x<row; x++)
        {
            tempi = 0;
            for(int i=1; i<row; i++)
            {
                tempj=0;
                for(int j=0; j<row; j++)
                {
                    if(j==x) continue;
                    else
                    {
                        temp.pp[tempi][tempj]=pp[i][j];
                        tempj++;
                    }
                }
                tempi++;
            }
            det = det + (pow(-1, x)* pp[0][x]* temp.determinant());
        }
    }
    return det;
}

SquareMatrix SquareMatrix::cofactor()
{
    SquareMatrix res(row);
    int tempi, tempj;
    SquareMatrix temp(row-1);
    for(int x=0; x<row; x++)
    {
        for(int y=0; y<col; y++)
        {
            tempi=0;
            tempj=0;
            for(int i=0; i<row; i++)
            {
                for(int j=0; j<col; j++)
                {
                    if(i!=x && j!=y)
                    {
                        temp.pp[tempi][tempj] = pp[i][j];
                        if(tempj<(col-2)) tempj++;
                        else
                        {
                            tempj=0;
                            tempi++;
                        }
                    }
                }
            }
            res.pp[x][y]= pow(-1, x+y) * temp.determinant();
        }
    }
    return res;
}

SquareMatrix SquareMatrix::transpose()
{
    SquareMatrix res(row);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            res.pp[j][i]= pp[i][j];
        }
    }
    return res;
}

SquareMatrix SquareMatrix::adjoint()
{
    SquareMatrix res(row);
    res = cofactor().transpose();
    return res;
}

SquareMatrix SquareMatrix::inverse()
{
    SquareMatrix res(row);
    res = adjoint();
    double det = determinant();
    if(det==0)
    {
        throw "Math Error: Attempt to divide by zero";
    }
    else
    {
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                res.pp[i][j] = res.pp[i][j]/det;
            }
        }
        return res;
    }
}

void SquareMatrix :: toeplitzDecomposition()
{
    Matrix res(row,col);
    res = *this + transpose();
    res = res.scalarMultiplication(0.5);
    cout << "SYMMETRIC MATRIX: " << endl;
    res.display();
    cout << endl;

    res = *this - transpose();
    res = res.scalarMultiplication(0.5);
    cout << "ANTI-SYMMETRIC MATRIX: " << endl;
    res.display();
}

void SquareMatrix::operations()
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
                SquareMatrix temp(row);
                temp = transpose();
                cout << "TRANSPOSE: " << endl;
                temp.display();
                break;
            }
            case 6:
            {
                editMatrix();
                cout << "NEW MATRIX: " << endl;
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
                cout << "COFACTOR MATRIX: " << endl;
                r.display();
                break;
            }
            case 9:
            {
                SquareMatrix r(row);
                r = adjoint();
                cout << "ADJOINT MATRIX: " << endl;
                r.display();
                break;
            }
            case 10:
            {
                double d;
                try
                {
                    SquareMatrix r(row);
                    r = inverse();
                    cout << "INVERSE: " << endl;
                    r.display();
                }
                catch(const char* str)
                {
                    cout << str << endl;
                }
                break;
            }
            case 11:
            {
                cout << "TOEPLITZ DECOMPOSITION: " << endl << endl;
                toeplitzDecomposition();
                break;
            }
            case 12:
            {
                Matrix triplet = tripletNotation();
                cout << "TRIPLET NOTATION: " << endl;
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

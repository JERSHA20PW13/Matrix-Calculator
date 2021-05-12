#include <iostream>
#include <cmath>
#include <conio.h>
#include "matrix.h"

using namespace std;

Matrix :: Matrix()
{
    row = 0;
    col = 0;
}

Matrix :: Matrix(int r,int c)
{
    row = r;
    col = c;

    pp = new double *[r];
    for(int i=0; i<r; i++)
        pp[i] = new double [c];

    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
            pp[i][j] = 0;
}

void Matrix :: setDimension(int r, int c)
{
    for(int i=0;i<row;i++)
        delete[] pp[i];
    delete[] pp;

    row = r;
    col = c;

    pp = new double *[r];
    for(int i=0; i<r; i++)
        pp[i] = new double [c];

    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
            pp[i][j] = 0;
}

void Matrix :: read()
{
    cout<<endl<<"Enter the matrix : "<<endl;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            cin>>pp[i][j];
        }
    }
}

void Matrix :: display() const
{
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            cout<< ((abs(pp[i][j]) < 0.00000000005)? 0.000: pp[i][j]) <<"\t";
            //cout << pp[i][j] << "\t";
        }
        cout<<endl<<endl;
    }
}

Matrix Matrix :: transpose()
{
    Matrix m(col,row);

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            m.pp[j][i] = this->pp[i][j];

    return m;
}

bool Matrix :: checkSquare()
{
    if(row == col)
        return true;
    else
        return false;
}

bool Matrix :: checkSymmetric()
{
    if(checkSquare())
    {
        Matrix m(row,col);
        m = transpose();

        if(m == *this)
            return true;
        return false;
    }
    else
        return false;
}

bool Matrix :: checkTriangular()
{
    if(checkSquare())
    {
        int flag = 1;

        //upper triangular check
        for(int i=1; i<row; i++)
        {
            for(int j=0; j<i; j++)
            {
                if(pp[i][j] != 0)
                {
                    flag = 0;
                    break;
                }
            }
            if(flag == 0)
                break;
        }

        if(flag)
            return true;

        //lower triangular check
        flag = 1;
        for(int i=0; i<row; i++)
        {
            for(int j=i+1; j<col; j++)
            {
                if(pp[i][j] != 0)
                {
                    flag = 0;
                    break;
                }
            }
            if(flag==0)
                break;
        }

        if(flag)
            return true;
        else
            return false;
    }
    else
        return false;
}

bool Matrix :: checkDiagonal()
{
    if(checkSquare())
    {
        for(int i=1; i<row; i++)
            for(int j=0; j<i; j++)
                if(pp[i][j] != 0)
                    return false;

        for(int i=0; i<row; i++)
            for(int j=i+1; j<col; j++)
                if(pp[i][j] != 0)
                    return false;

        return true;
    }
    else
        return false;
}

bool Matrix :: operator ==(Matrix m)
{
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            if(pp[i][j]!=m.pp[i][j])
                return false;
    return true;
}

Matrix Matrix :: operator +(Matrix m)
{
    Matrix r(row,col);
    for(int i=0; i<m.row; i++)
        for(int j=0; j<m.col; j++)
            r.pp[i][j] = pp[i][j] + m.pp[i][j];
    return r;
}

Matrix Matrix :: operator -(Matrix m)
{
    Matrix r(row,col);
    for(int i=0; i<m.row; i++)
        for(int j=0; j<m.col; j++)
            r.pp[i][j] = pp[i][j] - m.pp[i][j];
    return r;
}

Matrix Matrix :: operator *(Matrix m)
{
    Matrix r(row,m.col);
    for(int i=0; i<row; i++)
        for(int j=0; j<m.col; j++)
            for(int k=0; k<col; k++)
                r.pp[i][j] += pp[i][k] * m.pp[k][j];
    return r;
}

void Matrix :: editMatrix()
{
    int flag = 1;
    while(flag)
    {
        int r,c,num;
        cout<<"Enter row index : ";
        cin>>r;
        while(r<1 || r>row)
        {
            cout << "Invalid Index! Enter row index again: ";
            cin >> r;
        }
        cout<<"Enter column index : ";
        cin>>c;
        while(c<1 || c>col)
        {
            cout << "Invalid Index! Enter column index again: ";
            cin >> c;
        }
        cout<<"Enter new value : ";
        cin>>num;
        pp[r-1][c-1] = num;
        cout<<"Do you want to edit again? (0 - no , 1 - yes) : ";
        cin>>flag;
    }
}

Matrix Matrix :: scalarMultiplication(double k)
{
    Matrix r(row,col);
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            r.pp[i][j] = k * pp[i][j];
    return r;
}

Matrix Matrix :: tripletNotation()
{
    int c = 0;
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            if(pp[i][j] != 0)
                c++;

    Matrix t(c+1,3);
    t.pp[0][0] = row;
    t.pp[0][1] = col;
    t.pp[0][2] = c;
    int index = 1;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            if(pp[i][j]!=0)
            {
                t.pp[index][0] = i;
                t.pp[index][1] = j;
                t.pp[index][2] = pp[i][j];
                index++;
            }
        }
    }

    return t;
}

int Matrix :: getRow() const
{
    return row;
}

int Matrix :: getColumn() const
{
    return col;
}

double** Matrix :: getMatrix() const
{
    return pp;
}

void Matrix :: setElement(int r,int c,int elt)
{
    pp[r][c] = elt;
}

double Matrix :: getElement(int r,int c) const
{
    return pp[r][c];
}

Matrix::Matrix(const Matrix &m)
{
    row = m.row;
    col = m.col;
    pp = new double *[row];
    for(int i=0; i<row; i++)
        pp[i] = new double [col];

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            pp[i][j] = m.pp[i][j];
}

Matrix Matrix::operator =(const Matrix &m)
{
    row = m.row;
    col = m.col;
    pp = new double *[row];
    for(int i=0; i<row; i++)
        pp[i] = new double [col];

    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            pp[i][j] = m.pp[i][j];
    return *this;
}

void Matrix::operations()
{
    int x=1, choice;
    while(x)
    {
        cout << "_  _ ____ ___ ____ _ _  _    ____ ____ _    ____ _  _ _    ____ ___ ____ ____    "
"\n|\\/| |__|  |  |__/ |  \\/     |    |__| |    |    |  | |    |__|  |  |  | |__/   "
"\n|  | |  |  |  |  \\ | _/\\_    |___ |  | |___ |___ |__| |___ |  |  |  |__| |  \\    ";
        cout << endl << endl;

        cout << "MATRIX: " << endl;
        display();
        cout << "\t\tAvailable operations: " << endl;
        cout << "\t\t\t1. Add\n\t\t\t2. Subtract\n\t\t\t3. Scalar Multiplication\n\t\t\t4. Multiplication\n\t\t\t5. Transpose\n\t\t\t6. Edit Matrix\n\t\t\t7. Sparse matrix to triplet notation\n\t\t\t8. Back" << endl;
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
                Matrix temp(row, col);
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
                Matrix triplet = tripletNotation();
                cout << "TRIPLET NOTATION: " << endl;
                triplet.display();
                break;
            }
            case 8:
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

Matrix :: ~Matrix()
{
    //delete[] pp;
    for(int i=0;i<row;i++)
        delete[] pp[i];
    delete[] pp;
}


#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

class Matrix
{
    protected:
        int row, col;
        double **pp;

    public:
        Matrix();
        Matrix(int, int);
        Matrix(const Matrix&);
        Matrix operator =(const Matrix&);

        void setDimension(int, int);
        void read();
        void display() const;

        bool checkSquare();
        bool checkSymmetric();
        bool checkTriangular();
        bool checkDiagonal();
        bool operator ==(Matrix);

        Matrix operator +(Matrix);
        Matrix operator -(Matrix);
        Matrix operator *(Matrix);
        Matrix transpose();
        Matrix scalarMultiplication(double);
        Matrix tripletNotation();

        int getRow() const;
        int getColumn() const;
        double** getMatrix() const;
        void setElement(int,int,int);
        double getElement(int,int) const;
        void editMatrix();
        void operations();

        ~Matrix();
};

#endif // MATRIX_H_INCLUDED

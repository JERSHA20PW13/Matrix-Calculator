//application of matrix - cryptography
#include <iostream>
#include "matrix.h"
#include "square_matrix.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

//a utility function to encrypt user's message
bool encrypt(string file1, string file2, string file3)
{
    string message(""), file, text, num, matrixstr(""), numstr("");
    int len, x=0, y=0, n, m, i=0, order=0;
    double number;

    //opening file which contains matrix
    ifstream fin;
    fin.open(file3);
    if(!fin)
    {
        cout << "\nSystem error/File doesn't exist" << endl;
        return false;
    }
    while(fin)
    {
        getline(fin, num);
        matrixstr = matrixstr + num + "\n";
    }
    fin.close();

    while(matrixstr[i] != '\n')
    {
        if(matrixstr[i]== ' ')
        {
            order++;
        }
        i++;
    }
    n = order + 1;
    SquareMatrix encrm(n);

    for(int i=0; i<matrixstr.length(); i++)
    {

        if(matrixstr[i] != ' ' && matrixstr[i] != '\n')
            numstr = numstr + matrixstr[i];
        else
        {
            istringstream (numstr) >> number;
            numstr = "";
            encrm.setElement(x,y,number);
            y++;
            if(y==n)
            {
                y = 0;
                x++;
            }
            if(x==n)
                break;
        }
    }
    //cout << "The encryption matrix is " << endl;
    //encrm.display();

    //opening file which contains normal text
    fin.open(file1);
    if(!fin)
    {
        cout << "\nSystem error/File doesn't exist" << endl;
        return false;
    }
    while(fin)
    {
        getline(fin, text);
        message = message + text + "\n";
    }
    fin.close();
    len = message.length();
    m = ceil(len/(float)n);
    Matrix messm(m,n);
    x = 0,y = 0;
    for(int i=0; i<len; i++)
    {
        number = message[i];
        messm.setElement(x,y,number);
        y++;
        if(y==n)
        {
            y = 0;
            x++;
        }
        if(x==m)
            break;
    }
    //cout << "The message matrix is " << endl;
    //messm.display();

    Matrix emess(m,n);
    emess = messm*encrm;
    //emess.display();

    //opening file to write encrypted text
    ofstream fout;
    fout.open(file2);
    if(!fout)
    {
        cout << "\nSystem error" << endl;
        return false;
    }
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            number = emess.getElement(i, j);
            fout << number << " ";
        }
    }
    fout.close();
    return true;
}

bool decrypt(string file1, string file2, string file3)
{
    string file, num, matrixstr(""), numstr(""), demessage(""), messagestr("");
    int i=0, j=0, order=0, n, m, x=0, y=0, len=0;
    double number;

    //opening file which contains matrix
    ifstream fin;
    fin.open(file3);
    if(!fin)
    {
        cout << "\nSystem error/File doesn't exist" << endl;
        return false;
    }
    while(fin)
    {
        getline(fin,num);
        matrixstr = matrixstr + num + "\n";
    }
    fin.close();

    while(matrixstr[i] != '\n')
    {
        if(matrixstr[i]== ' ')
        {
            order++;
        }
        i++;
    }
    n = order + 1;
    SquareMatrix encrm(n);
    for(i=0; i<matrixstr.length(); i++)
    {
        if(matrixstr[i] != ' ' && matrixstr[i] != '\n')
            numstr = numstr + matrixstr[i];
        else
        {
            istringstream (numstr) >> number;
            numstr = "";
            encrm.setElement(x,y,number);
            y++;
            if(y==n)
            {
                y = 0;
                x++;
            }
            if(x==n)
                break;
        }
    }

    SquareMatrix decrm(n);
    decrm = encrm.inverse();
    //decrm.display();

    //opening file which contains encrypted message
    fin.open(file1);
    if(!fin)
    {
        cout << "\nSystem error/File doesn't exist" << endl;
        return false;
    }
    getline(fin,demessage);
    fin.close();
    for(i=0; i<demessage.length(); i++)
        if(demessage[i]== ' ')
            len++;
    len++;
    m = ceil(len/(float)n);
    Matrix message(m,n);
    x = 0,y = 0;
    for(i=0; i<demessage.length(); i++)
    {
        if(demessage[i] != ' ')
            numstr = numstr + demessage[i];
        else
        {
            istringstream (numstr) >> number;
            numstr = "";
            message.setElement(x,y,number);
            y++;
            if(y==n)
            {
                y = 0;
                x++;
            }
            if(x==m)
                break;
        }
    }
    //message.display();

    Matrix demess(m,n);
    demess = message*decrm;
    //demess.display();

    for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
        {
            number = demess.getElement(i,j);
            char ch = round(number);
            messagestr = messagestr + ch;
        }
    }

    //opening file to write decrypted message
    ofstream fout;
    fout.open(file2);
    if(!fout)
    {
        cout << "\nSystem error" << endl;
        return false;
    }
    fout << messagestr;
    fout.close();
}

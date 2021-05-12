#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include "matrix.h"
#include "square_matrix.h"
#include "symmetric_matrix.h"
#include "triangular_matrix.h"
#include "diagonal_matrix.h"

using namespace std;

bool encrypt(string, string, string);
bool decrypt(string, string, string);
bool set_password();
bool check_password();

void logging(string info)
{
    ofstream log;
    log.open("log.txt", ios_base::app);
    if(!log)
    {
        cerr << "System error!" << endl;
        return;
    }
    time_t now = time(0);
    char * timeNow = ctime(&now);
    log << timeNow << info << endl << endl;
    log.close();
}

//driver code
int main()
{
    int x = 1, choice, y = 1;

    while(x)
    {
        cout << "\t\tOBJECT COMPUTING LAB PACKAGE BY JERSHA HEARTLY X & TAMJID L" << endl << endl;
        cout << "1. MATRIX CALCULATOR" << endl;
        cout << "2. CRYPTOGRAPHY" << endl;
        cout << "3. EXIT" << endl;
        cout << "Enter what to perform : ";
        cin >> choice;
        switch(choice)
        {
            case 1:
            {
                logging("Matrix calculator accessed");

                system("CLS");
                cout << "_  _ ____ ___ ____ _ _  _    ____ ____ _    ____ _  _ _    ____ ___ ____ ____    "
"\n|\\/| |__|  |  |__/ |  \\/     |    |__| |    |    |  | |    |__|  |  |  | |__/   "
"\n|  | |  |  |  |  \\ | _/\\_    |___ |  | |___ |___ |__| |___ |  |  |  |__| |  \\    ";
                int r, c;
                cout<<"\n\n\nEnter number of rows : ";
                cin>>r;
                cout<<"Enter number of columns : ";
                cin>>c;

                Matrix *ptr = new Matrix(r,c);
                ptr->read();
                cout << endl;

                if(ptr->checkDiagonal())
                {
                    DiagonalMatrix dm(r);
                    dm = *ptr;
                    system("CLS");
                    dm.operations();
                }
                else if(ptr->checkSymmetric())
                {
                    SymmetricMatrix sm(r);
                    sm = *ptr;
                    system("CLS");
                    sm.operations();
                }
                else if(ptr->checkTriangular())
                {
                    TriangularMatrix tm(r);
                    tm = *ptr;
                    system("CLS");
                    tm.operations();
                }
                else if(ptr->checkSquare())
                {
                    SquareMatrix s(r);
                    s = *ptr;
                    system("CLS");
                    s.operations();
                }
                else
                {
                    Matrix m(r,c);
                    m = *ptr;
                    system("CLS");
                    m.operations();
                }
                delete ptr;
                break;
            }
            case 2:
            {
                system("CLS");
                cout << "____ ____ _   _ ___  ___ ____ ____ ____ ____ ___  _  _ _   _ "
"\n|    |__/  \\_/  |__]  |  |  | | __ |__/ |__| |__] |__|  \\_/  "
"\n|___ |  \\   |   |     |  |__| |__] |  \\ |  | |    |  |   |   ";
                cout << "\n\n";

                ifstream pwd("SEC.txt");
                if(!pwd)
                {
                    //pwd.close();
                    if(set_password())
                    {
                        cout << "\n\nPassword was set successfully!" << endl;
                        cout << "Now you can access 2. CRYPTOGRAPHY by entering your newly set password" << endl;
                        logging("New password set successfully");
                        cout << "\n\n\n\nPress any key to continue..." << endl;
                        getch();
                        system("CLS");
                    }
                }
                else
                {
                    pwd.close();
                    if(check_password())
                    {
                        cout << "\t\tACCESS GRANTED\n\n";
                        y = 1;
                        while(y)
                        {
                            int ch;
                            cout << "1. Encrypt" << endl;
                            cout << "2. Decrypt" << endl;
                            cout << "3. Back" << endl;
                            cout << "Enter what to perform : ";
                            cin >> ch;
                            switch(ch)
                            {
                                case 1:
                                {
                                    string file1, file2, file3;
                                    cout << "\nEnter file name of message with extension : ";
                                    cin >> file1;
                                    cout << "Enter name of file in which encrypted message is to be stored : ";
                                    cin >> file2;
                                    cout << "Enter file name of encryption matrix with extension : ";
                                    cin >> file3;
                                    if(encrypt(file1, file2, file3))
                                    {
                                        cout << "\nYour encrypted message is written in " << file2 << " file" << endl;
                                        logging("Encryption success");
                                        cout << "\n\n\n\nPress any key to continue..." << endl;
                                        getch();
                                        system("CLS");
                                    }
                                    else
                                    {
                                        cout << "Error encrypting" << endl;
                                        logging("Encryption failed");
                                        cout << "\n\n\n\nPress any key to continue..." << endl;
                                        getch();
                                        system("CLS");
                                    }
                                    break;
                                }
                                case 2:
                                {
                                    string file1, file2, file3;
                                    cout << "\nEnter file name of encoded text : ";
                                    cin >> file1;
                                    cout << "Enter name of file in which decrypted message is to be stored : ";
                                    cin >> file2;
                                    cout << "Enter file name of encrypted matrix with extension : ";
                                    cin >> file3;
                                    if(decrypt(file1, file2, file3))
                                    {
                                        cout << "\nYour decrypted message is written in " << file2 << " file" << endl;
                                        logging("Decryption success");
                                        cout << "\n\n\n\nPress any key to continue..." << endl;
                                        getch();
                                        system("CLS");
                                    }
                                    else
                                    {
                                        cout << "Error decrypting" << endl;
                                        logging("Decryption failed");
                                        cout << "\n\n\n\nPress any key to continue..." << endl;
                                        getch();
                                        system("CLS");
                                    }
                                    break;
                                }
                                case 3:
                                {
                                    y = 0;
                                    system("CLS");
                                    break;
                                }
                                default:
                                   cout << "INVALID INPUT !!!" << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "\t\tACCESS DENIED\n\n";
                    }
                }
                break;
            }
            case 3:
            {
                x = 0;
                break;
            }
            default:
                cout << "INVALID INPUT !!!" << endl;
        }
    }
    return 0;
}

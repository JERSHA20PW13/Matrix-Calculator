//login page
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <cstring>
#include <fstream>
#include <ctime>
using namespace std;

bool encrypt(string, string, string);
bool decrypt(string, string, string);
void logging(string);

//a utility function used to set new password
bool set_password()
{
    int i;
    char pass[25], confirm[25];
    ofstream pwd("SEC.txt");
    if(!pwd)
    {
        cout << "System error!" << endl;
        return false;
    }
    cout << "WELCOME! SET A PASSWORD TO SECURE YOUR ACTIONS!\n\n";
    cout << "\t\tEnter a password: ";
    i=0;
    pass[0]= getch();
    while(pass[i]!='\r')
    {
        if(pass[i]=='\b')
        {
            i--;
            cout << "\b \b";
            pass[i]=getch();
        }
        else
        {
            cout <<"*";
            i++;
            pass[i]=getch();
        }
    }
    pass[i]='\0';

    do
    {
        cout << "\n\t\tConfirm password: ";
        i=0;
        confirm[0]= getch();
        while(confirm[i]!='\r')
        {
            if(confirm[i]=='\b')
            {
                i--;
                cout << "\b \b";
                confirm[i]=getch();
            }
            else
            {
                cout << "*";
                i++;
                confirm[i]=getch();
            }
        }
        confirm[i]='\0';
        if(strcmp(pass,confirm)==0)
        {
            pwd << pass << "\n";
            pwd.close();
            encrypt("SEC.txt", "SEC.txt", "rand.txt");
            return true;
        }
        else
        {
            cout << "\nRe-entered password doesn't match!" << endl;
        }
    }while(strcmp(pass,confirm)!=0);
}

//a utility function used to check whether entered password is correct
bool check_password()
{
    ifstream pwd;
    int i;
    char pass[25], check[25];
    char ch;
    decrypt("SEC.txt", "SEC.txt", "rand.txt");

    while(1)
    {
        pwd.open("SEC.txt");
        if(!pwd)
        {
            cout << "System error!" << endl;
            return false;
        }
        pwd.close();
        i=0;
        cout << "Enter your password: ";
        pass[0]=getch();
        while(pass[i]!='\r')
        {
            if(pass[i]=='\b')
            {
                i--;
                cout << "\b \b";
                pass[i]=getch();
            }
            else
            {
                cout << "*";
                i++;
                pass[i]=getch();
            }
        }
        pass[i]='\0';
        pwd.open("SEC.txt");
        i=0;
        while(1)
        {
            pwd.get(ch);
            if(ch=='\n')
            {
                check[i]='\0';
                break;
            }
            else
            {
                check[i]=ch;
                i++;
            }
        }
        pwd.close();
        if(strcmp(pass, check)==0)
        {
            system("CLS");
            encrypt("SEC.txt", "SEC.txt", "rand.txt");
            logging("Logged in to cryptography");
            return true;
        }
        else
        {
            cout << "\n\nThe entered password is wrong!\n";
            string info = "ALERT! Failed attempt to login. Incorrect password entered: " + (string)pass;
            logging(info);
            cout << "Retry? (0=no, 1=yes): ";
            cin >> i;
            if(!i)
            {
                encrypt("SEC.txt", "SEC.txt", "rand.txt");
                return false;
                break;
            }
        }
    }
}

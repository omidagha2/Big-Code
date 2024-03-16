#include <string>
#include <vector>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "1m.cpp"

int main()
{
    string name;
    int age;
    char y;
    cout << "enter your name: ";
    getline(cin , name);
    cout << "enter your age: ";
    cin >> age;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

    cout << "\nWELLCOME TO ";
    SetConsoleTextAttribute(hConsole,FOREGROUND_RED); 
    cout << "IUSTZ ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    cout << "GAME " << name << "\n\n";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    while(true){
    cout << "1.existed" << "\n2.customize\n" << "(press \"1\" for choosing amoung existed characters and for customizing press \"2\")";
    y =_getch();
    characters ch;
    if (y=='1')
    {
        ch.displaychars();
        cin.get();
    } else if (y=='2'){
        cin.get();
    } else {
        cout << "unvalid choice\n";
        break;
    }
    }
    
}
   
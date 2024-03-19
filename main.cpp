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

    cout << "\nWELCOME TO ";
    SetConsoleTextAttribute(hConsole,FOREGROUND_RED); 
    cout << "IUSTZ ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    cout << "GAME " << name << "\n\n";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    while(true){
    cout << "1.existing" << "\n2.custom\n" << "(press \"1\" to choose among existing characters and \"2\" to create a custom character)\n";
    y =_getch();
    characters ch;
    if (y=='1')
    {
        ch.displaychars();
        cin.get();
    } else if (y=='2'){
        cin.get();
    } else {
        cout << "invalid choice\n";
        break;
    }
    }
    
}
   

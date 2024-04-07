#include <string>
#include <vector>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "1m.cpp"

int main()
{
    string name, namee;  int choice;
    char y;
    cout << "enter your name: ";
    getline(cin , name);
    setConsoleColor(1);
    cout << "\nWELLCOME TO ";
    setConsoleColor(2);
    cout << "IUSTZ ";
    setConsoleColor(1);
    cout << "GAME " << name << "\n\n";
    setConsoleColor(15);
    
    cout << "1.existed" << "\n2.customize\n" << "(press \"1\" for choosing amoung existed characters and for customizing press \"2\")";
    cin >> y;
    characters ch;
    if (y=='1')
    {
        ch.choice();
        
        
    } else if (y=='2'){
        
        cout << "choose a name for your character:\n";
        getline(cin ,namee);
        cout << "how strong you like to be?!\n" << "1.noob\n2.normal\n3.pro\n";
        cin >> choice;
        if (choice==1)
        {
            
        } else if (choice==2)
        {
            /* code */
        } else
        {
            /* code */
        }
        
        
        

    } else {
        cout << "unvalid choice\n";
    }
    }
    

   
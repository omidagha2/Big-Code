#include <iostream>
#include <string>
using namespace std;

class Item {
protected:
    int x = 9;
    string a[9] = {"Kalashnikov", "pistol", "graneid", "sks", "m14" ,"knife" , "bandaids" , "adrenaline" ," exir_st"};

    double prices[9] = {1000.0, 500.0, 200.0, 300.0, 800.0 , 200.0 ,300.0,290.0 ,219.0}; // Placeholder prices
    int quantities[9] = {10, 20, 15, 8, 5,4,7,9,1}; // Placeholder quantities

public:
    void set(int c) {
        x = c;
    }
};

class Store : public Item {
public:
    void print() {
        cout << "Items in store:" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "| Item Name     | Price ($) | Quantity |" << endl;
        cout << "-----------------------------------------" << endl;
        for (int i = 0; i < 5; i++) {
            cout << "| " << a[i] << " | $" << prices[i] << " | " << quantities[i] << " |" << endl;
        }
        cout << "-----------------------------------------" << endl;
    }

    void reduceQuantity(const string& itemName, int quantityToReduce) {
        for (int i = 0; i < 5; i++) {
            if (a[i] == itemName) {
                if (quantities[i] >= quantityToReduce) {
                    quantities[i] -= quantityToReduce;
                    cout << "Reduced " << quantityToReduce << " " << itemName << "(s) from the store." << endl;
                } else {
                    cout << "Insufficient quantity of " << itemName << " in the store." << endl;
                }
                return;
            }
        }
        cout << "Item not found in the store." << endl;
    }
};

int main() {
    Store b;
    b.print();

    string product;
    cin>>product;
    
    b.reduceQuantity(product, 1);

    // Print updated store
    b.print();

    
}

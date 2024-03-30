#include <iostream>
#include <string>
using namespace std;

class item {
protected:
    int x = 9;
    string a[5] = {"Kalashnikov", "pistol", "graneid", "sks", "m14"};

public:
    void set(int c) {
        x = c;
    }
};

class store : public item {
public:
    void print() {
        for (int i = 0; i < 5; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    store b;
    cout << "Items in store: ";
    b.print();
    return 0;
}

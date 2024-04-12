#include <iostream>
#include <string>

using namespace std;

class entity {
protected:
    string name;
    int age;
    string gender;
    int lvl;
    int hp;
    int dmg;
    int sta;

public:
    virtual void attack(entity* x) = 0;
    virtual ~entity() {} // Virtual destructor for safe polymorphic use

    entity(string argName, int argAge, string argGender, int argLVL = 1, int argHP = 0, int argDMG = 0, int argSTA = 0)
    : name(argName), age(argAge), gender(argGender), lvl(argLVL), hp(argHP), dmg(argDMG), sta(argSTA) {}
    
    string getname() const { return name; }
    int getlvl() const { return lvl; }
    int getdmg() const { return dmg; }
    int getsta() const { return sta; }
    int gethp() const { return hp; }
    friend class item;
};

class player : public entity {
public:
    player(string argName, int argAge, string argGender, int argLVL = 1, int argHP = 0, int argDMG = 0, int argSTA = 0)
    : entity(argName, argAge, argGender, argLVL, argHP, argDMG, argSTA) {}

    void attack(entity* x) override {
        // Implement attack logic
        cout << "Attacking " << x->getname() << endl;
    }
};

class item {
protected:
    // No hp here
    /*string Kalashnikov;
    string pistol;
    string graneid;
    string m16;
    string sks;
    string m14;
    string knife;
    string bandaids;
    string adrenaline;
    string exir_st;*/

    string a[9] = {"Kalashnikov", "pistol", "graneid", "sks", "m14" ,"knife" , "bandaids" , "adrenaline" ," exir_st"};
double prices[9] = {1000.0, 500.0, 200.0, 300.0, 800.0 , 200.0 ,300.0,290.0 ,219.0}; // Placeholder prices
    int quantities[9] = {10, 20, 15, 8, 5,4,7,9,1}; 

public:
    void set(entity& e, int a) {
        e.hp = a; // Set hp in the entity class
    }
    void damage_pistol(entity& e) {
        e.hp -= 50; // Damage hp in the entity class
    }
    void damage_Kalashnikov(entity& e){
        e.hp -= 30;
    }
    void damage_graneid(entity& e){
        e.hp -= 100;
    }
    void damage_m16(entity& e){
        e.hp -= 26;
    }
    void damage_sks(entity& e){
        e.hp -= 20;
    }
    void damage_m14(entity& e){
        e.hp -= 24;
    }
    void damage_knife(entity& e){
        e.hp -= 27;
    }
    void heal_bandaids(entity& e){
        e.hp += 20;
    }
    void heal_adrenaline(entity& e){
        e.hp += 40;
    }
    void heal_stamania( entity& e){
        e.sta+=40;
    }
};

class Store : public item {
public:
    void print() {
        cout << "Items in store:" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "| Item Name     | Price ($) | Quantity |" << endl;
        cout << "-----------------------------------------" << endl;
        for (int i = 0; i < 9; i++) {
            cout << "| " << a[i] << " | $" << prices[i] << " | " << quantities[i] << " |" << endl;
        }
        cout << "-----------------------------------------" << endl;
    }

    void reduceQuantity(const string& itemName, int quantityToReduce) {
        for (int i = 0; i < 9; i++) {
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
    player p("John Doe", 25, "Male", 1, 1000, 0, 0);

    item meow;
    meow.damage_pistol(p); // Apply damage to the player
    
    cout << "Player's remaining health: " << p.gethp()<<endl;
    

    Store b;
    b.print();

    string product;
    cin>>product;
    
    b.reduceQuantity(product, 1);

    // Print updated store
    b.print();
}
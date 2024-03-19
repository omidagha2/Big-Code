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
private:
    // No hp here
    string Kalashnikov;
    string pistol;
    string graneid;
    string m16;
    string sks;
    string m14;
    string knife;
    string bandaids;
    string adrenaline;
    string exir_st;

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

int main() {
    player p("John Doe", 25, "Male", 1, 1000, 0, 0);

    item meow;
    meow.damage_pistol(p); // Apply damage to the player
    
    cout << "Player's remaining health: " << p.gethp();
    return 0;
}
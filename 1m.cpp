#include <string>
#include <vector>
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

const int SKILLS_IMPLEMENTED = 2;

enum USETYPE{
    consumable,
    infinite
};

enum WPNTYPE{
    melee,
    bulletdamage,
    bow,
    explosive
};

enum MOD{
    common,
    //...
};

enum STATE{

};

class item{
private:
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
protected:
    int use_limit;
    int uses_left;
    int size;

public:
    item(int argU_Limit, int argU_Left, int argSize){}
    item(){}
};

class weapon: public item{
protected:
    MOD modifier;
    int dmg;
public:
    weapon(MOD argMod, int argDMG, int argSize)
    :item(infinite, infinite, argSize), modifier(argMod), dmg(argDMG){}
    
     
};


class entity{
protected:
    string name;
    int age;
    string gender; 
    int lvl;
    int hp;
    int dmg;
    int sta;

public:
    virtual void attack(entity* x)=0;

    entity()=default;
    entity(string argName, int argAge, string argGender, int argLVL=1, int argHP=0, int argDMG=0, int argSTA=0)
    :name(argName), age(argAge), gender(argGender), lvl(argLVL), hp(argHP), dmg(argDMG), sta(argSTA){}
    string getname() const {return name;}
    int getlvl() {return lvl;}
    int getdmg() {return dmg;}
    int getsta() {return sta;}
};

class human: public entity{
protected:
    item item_at_hand;
    vector<item> inventory;
    int skills[SKILLS_IMPLEMENTED];

public: 
    human(string argName, int argAge, string argGender, int argLVL=1, int argHP=0, int argDMG=0, int argSTA=0)
    : entity(argName, argAge, argGender, argLVL, argHP, argDMG, argSTA),item_at_hand(0,0,0) {
        
    }
    human(){}
    virtual void attack(entity* x){}
    void changeHeldItem();
   
};

class characters: public human{
    vector<human> chars;
public:
   
      characters() {
        // Directly initialize the characters in the constructor
        chars.emplace_back("Thalion", 20, "Male", 1, 100, 10, 10);
        chars.emplace_back("Eirwyn", 25, "Male", 1, 110, 20, 20);
        chars.emplace_back("Brondar", 20, "Male", 1, 120, 20, 30);
        chars.emplace_back("Mirelle", 20, "Female", 1, 150, 45, 35);
        chars.emplace_back("Kaelum", 20, "Male", 1, 200, 50, 50);
        chars.emplace_back("Seraphina", 20, "Female", 1, 190, 60, 45); 
        chars.emplace_back("Draxen", 20, "Male", 1, 105, 20, 25);
        chars.emplace_back("Arianya", 20, "Female", 1, 130, 10, 35);
        chars.emplace_back("Fenris", 20, "Male", 1, 300, 65, 40);
        chars.emplace_back("Lyrielle", 20, "Female", 1, 500, 100, 100);
    }
    
    void displaychars(){
        cout << "you can choose..\n";
        for (int i = 0; i < chars.size(); i++)
        {
            cout << (i+1) << ". " << "Name: " << chars[i].getname() << endl << "Level: " << chars[i].getlvl() << endl;
            cout << "Damage: " << chars[i].getdmg() << endl << "Stamina: " << chars[i].getsta() << endl;
        }
        
    }
    bool isDefeated() const {

        return hp <= 0;
    }

};
class HumanEnemy: public human{
     bool isboss;
public:
    HumanEnemy(bool boss=false):isboss(boss) {}
};
class enemies: public HumanEnemy{
    vector<human> enemy;
public:
    enemies() {
        enemy.emplace_back("Stenchurion", 20, "Male", 1, 100, 5, 15);
        enemy.emplace_back("Cannibelle", 20, "Female", 1, 100, 7, 10);
        enemy.emplace_back("Magmalice", 20, "Male", 1, 200, 15, 10);
        enemy.emplace_back("Salamarauder", 20, "Female", 1, 150, 10, 15);
        enemy.emplace_back("Bewarewolf", 20, "Male", 1, 100, 15, 10);
        enemy.emplace_back("Lunatick", 20, "Male", 1, 120, 20, 10);

    }
};
class HenchMan: public HumanEnemy{

};

class HumanBoss: public HumanEnemy{

};

void setConsoleColor(int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout.flush();
    SetConsoleTextAttribute(hConsole, color);
}
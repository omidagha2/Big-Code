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
    
    //virtual void attack(entity*){};
};

class firearm: public weapon{

};

class melee: public weapon{

};

class pistol: public firearm{

};

class rifle: public firearm{

};

class grenade_launcher: public firearm{

};

class knife: public melee{

};

class club: public melee{

};

class consumable: public item{

};

class throwable: public consumable{

};

class status_item: public consumable{

};

class recovery_item: public consumable{

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
    //virtual void attack(entity*)=0;

    entity(){}
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
   // virtual void attack(entity*);
    void changeHeldItem();
   
};

class characters: public human{
    vector<human> chars;
public:
   
      characters() {
        // Directly initialize the characters in the constructor
        chars.emplace_back("Thalion", 20, "Male", 1, 100, 10, 10);
        chars.emplace_back("Eirwyn", 25, "Male", 2, 110, 20, 20);
        chars.emplace_back("Brondar", 20, "Male", 3, 120, 20, 30);
        chars.emplace_back("Mirelle", 20, "Female", 4, 150, 45, 35);
        chars.emplace_back("Kaelum", 20, "Male", 5, 200, 50, 50);
        chars.emplace_back("Seraphina", 20, "Female", 5, 190, 60, 45); 
        chars.emplace_back("Draxen", 20, "Male", 2, 105, 20, 25);
        chars.emplace_back("Arianya", 20, "Female", 3, 130, 10, 35);
        chars.emplace_back("Fenris", 20, "Male", 7, 300, 65, 40);
        chars.emplace_back("Lyrielle", 20, "Female", 10, 500, 100, 100);
    }
    
    void displaychars(){
        cout << "you can choose..\n";
        for (int i = 0; i < chars.size(); i++)
        {
            cout << (i+1) << ". " << "Name: " << chars[i].getname() << endl << "Level: " << chars[i].getlvl() << endl;
            cout << "Damage: " << chars[i].getdmg() << endl << "Stamina: " << chars[i].getsta() << endl;
        }
        
    }
};

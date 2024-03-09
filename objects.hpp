#include <string>
#include <vector>
#include <iostream>
using namespace std;

class entity;

const int SKILLS_IMPLEMENTED = 2;
enum STAGE{
    START_MENU,
    LVL1,
    LVL2,
    LVL3
};

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

//todo: use templates to make more reusable
class dict{
    vector<string> keys;
    vector<double> values;

public:
    dict(vector<string> argKeys, vector<double> argVals){
        keys = argKeys;
        values = argVals;
    };
};

class item{
protected:
    string name;
    int use_limit;
    int uses_left;
    int size;

public:
    item(string argName, int argU_Limit, int argU_Left, int argSize)
    :name(argName), use_limit(argU_Limit), uses_left(argU_Left), size(argSize){};
    string getname();
    void setName(string argName);
};

class weapon: public item{
protected:
    MOD modifier;
    int dmg;
public:
    weapon(string argName, MOD argMod, int argDMG, int argSize)
    :item(argName, infinite, infinite, argSize), modifier(argMod), dmg(argDMG){};
    
    virtual void attack(entity*){};
};

class firearm: public weapon{

};

class melee: public weapon{

};

// class pistol: public firearm{

// };

// class rifle: public firearm{

// };

// class grenade_launcher: public firearm{

// };

// class knife: public melee{

// };

// class club: public melee{

// };

class consumable: public item{

};

class throwable: public consumable{

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
    // virtual void attack(entity*)=0;
    void hi(){};

    entity();
    entity(string argName, int argAge, string argGender, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
    :name(argName), age(argAge), gender(argGender), lvl(argLVL), hp(argHP), dmg(argDMG), sta(argSTA){};

};

class human: public entity{
protected:
    item* item_at_hand;
    vector<item> inventory;
    int skills[SKILLS_IMPLEMENTED];

public: 
    human(string argName, int argAge, string argGender, vector<item> argInv, item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
    :entity(argName, argAge, argGender, argLVL, argHP, argDMG, argSTA){
        item_at_hand = argItemAtHandPTR;
        inventory = argInv;
    };
    virtual void attack(entity*){};
    void changeHeldItem(item* argItem){item_at_hand = argItem;};
    string getname(){return name;};
    vector<item>* getInv(){return &inventory;};
};

class player: public human{

public:
    player(string argName, int argAge, string argGender, vector<item> argInv={}, item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
    :human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argHP){};
};

class enemy: public entity{
protected:
    STATE current_state;
    vector<STATE> available_states;
public:
    void attack(human*);
};

class HumanEnemy: public human{

};

// class HenchMan: public HumanEnemy{

// };

// class HumanBoss: public HumanEnemy{

// };

class zombie: public enemy{

};

class CommonHusk: public zombie{

};

class Juggernaut: public zombie{

};

class MENU{
    vector<string> choices;
    
public:
    void choice1(){};
    void choice2(){};
    void choice3(){};
    //...
};

class Game{
    STAGE stage;
    MENU startmenu;
};

class COMBAT{
    //has a return result function. currently a stub
    vector<entity*> enemies;
    vector<entity*> allies;


};
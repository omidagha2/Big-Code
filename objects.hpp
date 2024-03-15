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

enum ACTION{
    heal, 
    damage,
    stamina,
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
//healing, 
//don't worry about stamina
//stamina is only used for running vs. attacking. maybe they can choose between attacking and building up stamina to run

class item{
protected:
    string name;
    int use_limit;
    int uses_left;
    int size;

public:
    item(string argName, int argU_Limit, int argU_Left, int argSize)
    :name(argName), use_limit(argU_Limit), uses_left(argU_Left), size(argSize){};
    string getname(){return name;};
    void setName(string argName){name = argName;};
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

// class : public consumable{

// };

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
    human(string argName, int argAge, string argGender, vector<item> argInv={}, item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
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
    string dialogue;
    player* target;

public: 
    HumanEnemy(string argName, int argAge, string argGender, vector<item> argInv={}, item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
    :human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argHP){};


//they add the thing they can get the most possible use out of 
//a use percent calculator
//private multipliers

//state fine: the enemy wants to 1 do the most damage, 2 be left on a good amount of hp, 3 

//maybe no need to have an evaluate funciton if you have the use% funciton
//*final plan: have the use% function, add the things you can use more than 90% of to some list, then randomly use 2 of thsoe things.
//items can have tiers. the AI doesn't add low tier items to the list
//this will be for the fine state
//maybe they can just differentiate levels, if the player is too strong they try to run
//if they see they can't defeat the player they build up stamina to run
//maybe a skill calculator, if you use something like undertale's attack, the enemy might see h=how good you are at dealing the most of your damage. 

//when will enemy use buffs? 
    //when he can use the highest damage weapon he has/deal the most damage. also won't use it if he can already deal that damage and the buff has no effect on damage.
    //unless it's a critical state. according to lore, he'd like to live more than defeat you as an enemy, except maybe the final boss.
    //maybe different bosses have different priorities.
    
    //currently finish the fine state. states only change modifiers for now

    int evaluate(){
        return hp + sta;
    };

    int useEfficiency(){
        //items should have a max stat? giving thing
    };

    void use(item thing){};
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
    entity* friends;
    entity* foes;
    bool is_running;
    

public:
    COMBAT(entity* argFriend, entity* argFoe)
    :foes(argFoe), friends(argFriend){is_running = false;};
    entity* getFriend(){return friends;};
    entity* getFoe(){return foes;};
    // void action(entity* towho, pair <action, value>);
    
};


#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Entity;
class CombatController;
const int SKILLS_IMPLEMENTED = 2;
enum class Stage{
    START_MENU,
    LVL1,
    LVL2,
    LVL3
};

enum UseType{
    CONSUMABLE,
    INFINITE
};

enum class DamageType{
    SLICE,
    IMPACT,

};


enum class MOD{
    COMMON,
    //...
};

enum class EnemyState{

};

// enum ACTION{ //if implementing a command system for combat controller
//     HEAL, 
//     DAMAGE,
//     STAMINA,
// };

// // //todo: use templates to make more reusable
// // class dict{
// //     vector<string> keys;
// //     vector<double> values;

// // public:
// //     dict(vector<string> argKeys, vector<double> argVals){
// //         keys = argKeys;
// //         values = argVals;
// //     };
// // };
//healing, 
//don't worry about stamina
//stamina is only used for running vs. attacking. maybe they can choose between attacking and building up stamina to run

class Item{
protected:
    string name;
    int use_limit;
    int uses_left;
    int size;

public:
    Item(string argName, int argU_Limit, int argU_Left, int argSize=1)
    :name(argName), use_limit(argU_Limit), uses_left(argU_Left), size(argSize){};
    string getname(){return name;};
    void setName(string argName){name = argName;};
    string type(){
        if (dynamic_cast<Weapon*>(this) != nullptr) return "weapon";
        elif (dynamic_cast<consumable*>(this) != nullptr) return "consumable";
        //...
    }
    int getUseLimit(){return use_limit;}
    int getUsesLeft(){return uses_left;}
    void decrementUsesLeft(int num=1){uses_left-= num;}
};

class Weapon: public Item{
protected:
    DamageType damage_type;
    MOD modifier;
    int dmg;

public:
    Weapon(string argName, MOD argMod, int argDMG, int argSize)
    :Item(argName, INFINITE, INFINITE, argSize), modifier(argMod), dmg(argDMG){};
    
    virtual void attack(Entity*){};
};

class firearm: public Weapon{

};

class melee: public Weapon{

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

//!haven't used encapsulation for now, write correct access modifier stuff later.
class Consumable: public Item{

};

class Throwawble: public Consumable{
    DamageType dmgtype;
    int damage;
};

class Healing: public Consumable{
    int value;
};

class StaminaRecovery: public Consumable{
    int value;
}


class Entity{
    friend CombatController;
protected:
    string name;
    int age;
    string gender; 
    int lvl;
    int hp;
    int max_hp;
    int dmg;
    int sta;
    int max_sta;

public:
    // virtual void attack(Entity*)=0;

    Entity();
    Entity(string argName, int argAge, string argGender, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
    :name(argName), age(argAge), gender(argGender), lvl(argLVL), hp(argHP), dmg(argDMG), sta(argSTA){};

};

class Human: public Entity{
protected:
    Item* item_at_hand;
    vector<Item> inventory;
    int skills[SKILLS_IMPLEMENTED];

public: 
    Human(string argName, int argAge, string argGender, vector<Item> argInv={}, Item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
    :Entity(argName, argAge, argGender, argLVL, argHP, argDMG, argSTA){
        item_at_hand = argItemAtHandPTR;
        inventory = argInv;
    }
    virtual void attack(Entity*){}
    void changeHeldItem(Item* argItem){item_at_hand = argItem;}
    string getname(){return name;}
    vector<Item>* getInv(){return &inventory;}

    void consume(Consumable* item){//currently only for healing
        if (item->getUseLimit() == CONSUMABLE){item->decrementUsesLeft();}
        if (dynamic_cast<Healing>(item) != nullptr){ //?does this do the cast here? I've assumed it does
            hp+= item->value;
            if (hp > max_hp) hp = max_hp;
        }
        if (item->getUsesLeft() <= 0){
            //remove from inventory (syntax highlighting and suggestions not working)
        }
    }
    
};

class Player: public Human{

public:
    Player(string argName, int argAge, string argGender, vector<Item> argInv={}, Item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
    :Human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argHP){};
};

class Enemy: public Entity{
protected:
    EnemyState current_State;
    vector<EnemyState> available_States;
public:
    void attack(Human*);
};

class HumanEnemy: public Human{
    string dialogue;
    Player* target;

public: 
    HumanEnemy(string argName, int argAge, string argGender, vector<Item> argInv={}, Item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
    :Human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argHP){};


//they add the thing they can get the most possible use out of 
//a use percent calculator
//private multipliers

//State fine: the enemy wants to 1 do the most damage, 2 be left on a good amount of hp, 3 

//maybe no need to have an evaluate funciton if you have the use% funciton
//*final plan: have the use% function, add the things you can use more than 90% of to some list, then randomly use 2 of thsoe things.
//Items can have tiers. the AI doesn't add low tier Items to the list
//this will be for the fine State
//maybe they can just differentiate levels, if the player is too strong they try to run
//if they see they can't defeat the player they build up stamina to run
//maybe a skill calculator, if you use something like undertale's attack, the enemy might see h=how good you are at dealing the most of your damage. 

//when will enemy use buffs? 
    //when he can use the highest damage weapon he has/deal the most damage. also won't use it if he can already deal that damage and the buff has no effect on damage.
    //unless it's a critical State. according to lore, he'd like to live more than defeat you as an enemy, except maybe the final boss.
    //maybe different bosses have different priorities.
    
    //currently finish the fine State. States only change modifiers for now

    int evaluate(){ //this would mean you have to create new objects to evaluate every time. 
        return hp + sta;
    };

    int useEfficiency(){
        //Items should have a max stat? giving thing
    };

    void use(Item thing){};
};

// class HenchMan: public HumanEnemy{
 
// };

// class HumanBoss: public HumanEnemy{

// };

class zombie: public Enemy{

};

class CommonHusk: public zombie{

};

class Juggernaut: public zombie{

};

class Menu{
    vector<string> choices;
    
public:
    void choice1(){};
    void choice2(){};
    void choice3(){};
    //...
};

class Game{
    Stage stage;
    Menu startmenu;
};


class CombatController{
    //
    //has a return result function. currently a stub is enough. maybe put it in the destructor?
    Entity the_friend;
    Entity the_foe;
    
public:
    CombatController(Entity& argFriend, Entity& argFoe)
    :the_foe(argFoe), the_friend(argFriend){
        while (argFriend.hp > 0 && argFoe.hp > 0){
            cout << argFriend.hp << ' ' << argFoe.hp << endl;
            return;
            //update display
            //prompt user
            //do player actions
            //do enemy actions
        };
    };
    Entity& getFriend(){return the_friend;};
    Entity& getFoe(){return the_foe;};
    // void action(Entity* towho, pair <action, value>);
    
};

HumanEnemy Human_enemy_generator(int lvl){

}

class Display{};
class SombatDisplay: public Display{};
class ShopDisplay: public Display{};
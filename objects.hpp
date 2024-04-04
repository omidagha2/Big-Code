#include <string>
#include <vector>
#include <iostream>
#include "items.hpp"
using namespace std;

class Entity;
class CombatController;
class Weapon;
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
    SLICE, IMPACT,
};


enum class MOD{
    COMMON,
    //...
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

    virtual string getType(){
        return "Item";
    }

    int getUseLimit(){return use_limit;}
    int getUsesLeft(){return uses_left;}
    void decrementUsesLeft(int num=1){uses_left-= num;}
    virtual void UseFunction()=0;
    

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
    virtual string getType(){
        return "Weapon";
    }
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

public: 
    string getType(){
        return "Consumable";
    }
};

class Throwable: public Consumable{
    DamageType dmgtype;
    int damage;
};

class Restorative: public Consumable{
    int hp_value;
    int sta_value;
public:
    string getType(){
        return "Rs";
    }
};


class Entity{
    enum class Type{
        //stuff to replace the strings with
    };
    friend CombatController;
protected:
    string name;
    int age;
    string gender; 
    int lvl;
    int hp; //maybe hp can instead be a percentage of the max hp, to get rid of some ai calculations
    int max_hp;
    int dmg;
    int sta;
    int max_sta;

public:
    // virtual void attack(Entity*)=0;

    Entity();
    Entity(string argName, int argAge, string argGender, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
    :name(argName), age(argAge), gender(argGender), lvl(argLVL), hp(argHP), dmg(argDMG), sta(argSTA){};
    virtual string getType(){
        return "Entity";
    };
    virtual bool isAlive(){
        return hp>0;
    }
    int getHp(){return hp;}
    int getSta(){return sta;}
    int getHpMax(){return max_hp;}
    int getStaMax(){return max_sta;}

    int hpFullPercent(){
        if (max_hp < 1) 
            return NULL;
        return hp*100/max_hp;
    }

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
    virtual string getType(){
        return "Human";
    }
    string getname(){return name;}
    vector<Item>* getInv(){return &inventory;}
};

class Player: public Human{
public:
    Player(string argName, int argAge, string argGender, vector<Item> argInv={}, Item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
    :Human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argHP){};

    virtual string getType(){
        return "Player";
    }


};


//methods that mutate object data should all be here.
//
class EnemyController{
    virtual void takedamage();
    virtual void changeState();
    virtual void dealdamage(Player*);
};

class SimpleController: public EnemyController{
    Enemy* enemy;
    
};

//a placeholder implementation, to be replaced with mvc. 
class Enemy: public Entity{
protected:
    // EnemyStatesSimple current_State;
    // vector<EnemyStatesSimple> available_States;
public:
    virtual void attack(Player*){};
    virtual string getType(){
        return "Enemy";
    }

};


class HumanEnemy: public Human{
    string dialogue;
    Player* target; 

public: 
    HumanEnemy(string argName, int argAge, string argGender, vector<Item> argInv={}, Item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
    :Human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argHP){

    };
    
    virtual string getType(){
        return "HumanEnemy";
    }

    int useEfficiency(){
        //if items had a max usage variable things would be very easy here. however, it would be harder when we get to making the factory and level generators.
    };

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
    Entity* friendPTR;
    Entity* foePTR;
    
public:
    
    static CombatController& GetInstance(){
        static CombatController combatInstance;
        return combatInstance;
    }

    static Entity* getFriendPTR() {return CombatController::GetInstance().imp_getFriendPTR();}
    static Entity* getFoePTR() {return CombatController::GetInstance().imp_getFoePT();}
private:
    Entity* imp_getFriendPTR(){return friendPTR;}
    Entity* imp_getFoePT(){return foePTR;}

    void Imp_GameLoop(){
        while (friendPTR->isAlive() && foePTR-> isAlive()){

        }
    }
    // void action(Entity* towho, pair <action, value>);
    
};

// HumanEnemy Human_enemy_generator(int lvl){

// }

class Display{
    
};
class SombatDisplay: public Display{};
class ShopDisplay: public Display{};
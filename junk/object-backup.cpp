#include <string>
#include <vector>
#include <iostream>
#include "items.hpp"
using namespace std;

class DamageComponent;
class Entity;
class CombatController;
class Weapon;
class HumanEnemy;
class Human;
class Player;

class Item{
    friend class HumanEnemy;
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
};

class Weapon: public Item{

protected:
    enum UseType{
    CONSUMABLE,
    INFINITE
    };
    enum MOD{};
    int dmg;
    MOD modifier;

public:
    Weapon(string argName, MOD argMod, int argDMG, int argSize)
    :Item(argName, INFINITE, INFINITE, argSize), modifier(argMod), dmg(argDMG){};
    
    virtual void attack(Entity*){};
    virtual string getType(){
        return "Weapon";
    }
};

class firearm: public Weapon{
    //takes pointer to a character's ammo box
};

class melee: public Weapon{

};

class ValuedComponent{
protected:
    int max_value;
    int value;
public:
    virtual int usePercent(){return value*100/max_value;};
    virtual int getValue(){return value;}
    virtual string getType(){return "ValuedComponent";}

    virtual void setVal(int val){
        value = val;
    }
    virtual int getVal(){return value;}
    virtual int getMaxVal(){return max_value;}
    
};



struct Stat{
    class HealthComponent: public ValuedComponent{
        friend HumanEnemy;
        friend class EnemyModel1;
    public:
        virtual string getType(){return "HealthComponent";}
        HealthComponent(int v, int mv=-1){
            if (mv==-1)
                max_value = v;
            else
                max_value = mv;
            value = v;
        }
    };
    class StaminaComponent: public ValuedComponent{
        friend HumanEnemy;
        friend class EnemyModel1;
    public:
        virtual string getType(){return "StaminaComponent";}
        StaminaComponent(int v, int mv=-1){
            if (mv==-1)
                max_value = v;
            else
                max_value = mv;
            value = v;
        }
    };
};

struct Damage_Type{
    
};

class Consumable: public Item{
    vector<ValuedComponent> valueComponents;
public: 

    Consumable(string name, int use_limit, int uses_left, vector<ValuedComponent> VCs={}, int size=1): Item(name, use_limit, uses_left, size){
        valueComponents = VCs;
    };

    void addVC(ValuedComponent vc){
        valueComponents.push_back(vc);
    }

    string getType(){
        return "Consumable";
    }
    
    vector<ValuedComponent>* getValueComponents(){return &valueComponents;}
    void apply(Entity* entity){
        for (ValuedComponent v: valueComponents){
            entity->consumeComponent(v);
            //do something with v if v is an object of some sort. maybe remove it, etc.
        }
    }
};

class Throwable: public Item{
    int damage;
public:
    string getType(){
        return "Throwable";
    }
};

class Entity{
    friend DamageComponent;
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

    Entity(){};
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
    int getLVL(){return lvl;}
    int getDMG(){return dmg;}

    int heal(int amount){//a multiplier of some sort
        hp = min(max_hp, hp+amount);
    }

    int increaseStamina(int amount){
        sta = min(max_sta, sta + amount);
    }

    virtual int calculateDmg(int damage){return damage;}
    
    virtual void takeDamage(int damage){//make damage a component based class
        hp -= calculateDmg(damage);
    }

    int hpFullPercent(){
        if (max_hp < 1) 
            return -1;
        return hp*100/max_hp;
    }

    int staminaFullPercent(){
        if (max_sta < 1)
            return -1;
        return sta*100/max_sta;
    }

    virtual void consumeComponent(ValuedComponent vc){
        string type = vc.getType();
        if (type == "HealthComponent"){
            this->heal(vc.getValue());
        }
        else if (type == "StaminaComponent"){
            this->increaseStamina(vc.getValue());
        }
    }


};

class Human: public Entity{
protected:
    Item* item_at_hand;
    vector<Item> inventory;

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
    friend DamageComponent;
public:
    Player(string argName, int argAge, string argGender, vector<Item> argInv={}, Item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
    :Human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argHP){};

    virtual string getType(){
        return "Player";
    }
};



class Enemy: public Entity{
protected:
public:
    virtual void attack(Player*){};
    virtual string getType(){
        return "Enemy";
    }

};

class HumanEnemy: public Human{
    string dialogue;
    Player* target; 
    friend class EnemyModel1;

public: 
    HumanEnemy(string argName, int argAge, string argGender, vector<Item> argInv={}, Item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100)
    :Human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argHP){

    }
    
    virtual string getType(){
        return "HumanEnemy";
    }

    int useEfficiency(){

    }

    void updateInventory(){
        Item* i = &*inventory.begin();
        while (i != &*inventory.end()){
            if (i->getType() == "Consumable"){
                Consumable* conptr = dynamic_cast<Consumable*>(i);
                for (ValuedComponent vc: *conptr->getValueComponents()){
                    ValuedComponent* vcptr = &vc;
                    if (Stat::HealthComponent* componentPTR = dynamic_cast<Stat::HealthComponent*>(vcptr)){
                        componentPTR->setVal(min(this->max_hp - this->hp, componentPTR->getMaxVal()));
                    }
                    if (Stat::StaminaComponent* componentPTR = dynamic_cast<Stat::StaminaComponent*>(vcptr)){
                        componentPTR->setVal(min(this->max_sta - this->sta, componentPTR->getMaxVal()));
                    }
                };
            }
        }
    }
    
};




class DamageComponent{
    int damage;
protected:
public:
    virtual int simulateDamage(Entity* entity){
        return entity->calculateDmg(damage);
    }
    virtual int deal(Entity* entity){

    }
};
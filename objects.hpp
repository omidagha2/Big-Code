#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <windows.h>
#include "items.hpp"
#include <conio.h>
using namespace std;



const int SP_CHAR_DELAY_DEFAULT = 30;
const int SP_PAR_DELAY_DEFAULT = 1000;



class DamageComponent;
class Entity;
class CombatController;
class Weapon;
class HumanEnemy;
class Human;
class Player;



namespace utils{
    enum Color{
        ORANGE,
        RED,
        GREEN,
        BLUE,
        WHITE

    };
    void slowPrint(string prompt, Color color=WHITE, double char_delay_ms=SP_CHAR_DELAY_DEFAULT){
        for (char c: prompt){
            cout << c;
            Sleep(char_delay_ms);
        }
    }
    void slowPrintPrompts(vector<string> prompts, Color color=WHITE, double char_delay_ms=SP_CHAR_DELAY_DEFAULT, double sentence_delay_ms=SP_PAR_DELAY_DEFAULT, string sentence_sep = "\n"){
        for (int i = 0; i < prompts.size(); i++){    
            for (char c: prompts[i]){
                cout << c;
                Sleep(char_delay_ms);
            }
            Sleep(sentence_delay_ms);
            if (i != prompts.size()) cout << sentence_sep;
        }
    }
    void cls(){
        system("cls");
    }
    void cll() {
    }
    char waitForInpt(){
        while(true){
            if (kbhit()) return getch();
        }
    }
}

class Item{
    friend class HumanEnemy;
protected:
    Human* owner;
    string name;
    int use_limit;
    int uses_left;
    int size;

public:
    Item(string argName, int argU_Limit, int argU_Left, int argSize=1);   string getname(){return name;};
    void setName(string argName);

    virtual string getType();

    int getUseLimit();
    int getUsesLeft();
    void decrementUsesLeft(int num=1);
    virtual void putInInv(Human* human);
};


class Weapon: public Item{

protected:
    enum MOD{};
    int dmg;
    MOD modifier;

public:
    Weapon(string argName, MOD argMod, int argDMG, int argSize);
    
    virtual void attack(Entity*);
    virtual string getType();
};

class firearm: public Weapon{
    //takes pointer to a character's ammo box
};

class melee: public Weapon{

};

struct SpecialWeaponFunction{

};

class ValuedComponent {
protected:
    int max_value;
    int value;
public:
    virtual int usePercent();
    virtual string getType();
    virtual void setVal(int val);
    virtual int getVal();
    virtual int getMaxVal();
};


struct Stat {
    class HealthComponent : public ValuedComponent {
    public:
        HealthComponent(int v, int mv = -1);
        string getType() override;
    };

    class StaminaComponent : public ValuedComponent {
    public:
        StaminaComponent(int v, int mv = -1);
        string getType() override;
    };
};


struct Damage_Type{
    
};


class Consumable: public Item {
    vector<ValuedComponent*> valueComponents;
public: 
    Consumable(string name, int use_limit, int uses_left, vector<ValuedComponent*> VCs={}, int size=1);
    void addVC(ValuedComponent* vc);
    string getType();
    vector<ValuedComponent*>& getValueComponents();
    //switch out the inheritance just for types and the other thing

    void apply(Entity* entity);
    void update();
};

class Throwable: public Item {
    int damage;
public:
    Throwable(int damage);
    string getType();
};


class Entity {
    // Assume friend classes and enum are declared here
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
    Entity();
    Entity(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, int argSTA);
    virtual string getType();
    virtual bool isAlive();
    int getHp();
    string getname();
    int getSta();
    int getHpMax();
    int getStaMax();
    int getLVL();
    int getDMG();
    void heal(int amount);
    void increaseStamina(int amount);
    virtual int calculateDmg(int damage);
    void takeDamage(int damage);
    int hpFullPercent();
    int staminaFullPercent();
    virtual void consumeComponent(ValuedComponent *vc);
    virtual void dealDamage(int amount, Entity* entity);

};


class Human: public Entity {
protected:
    Item* item_at_hand;
    vector<Item*> inventory;

public:
    Human(string argName, int argAge, string argGender, vector<Item*> argInv={}, Item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100);
    virtual string getType();
    string getname();
    vector<Item*> getInv();
    vector<Consumable*> getConsumablesInv();
    virtual void use(Item*);
    virtual void useWeapon(Weapon*, Entity*);
    virtual void useThrowable(Throwable*, Entity*);
    virtual void useConsumable(Consumable*);
    virtual void takeInInv(Item* item);
    virtual void consumeConsumable(Item* consumable);
    virtual void removeFromInv(Item* item);

};


class Player: public Human {
    // Assuming DamageComponent is correctly implemented elsewhere.
    friend class DamageComponent;

public:
    Player(string argName, int argAge, string argGender, vector<Item*> argInv={}, Item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100);
    virtual string getType();
    int atkBar();
    virtual void attack(Entity* entity);
    int menuPrompt();
    void inventoryPrompt(); //throwable, consumable, ammo_box, needle, ...
    void meleePrompt();
    void shootPrompt();
};


class Enemy : public Entity {
public:
    virtual void attack(Player* player);
    virtual string getType() override;
};



class HumanEnemy : public Human {
    string dialogue;
    Player* target; 
public:
    HumanEnemy(string argName, int argAge, string argGender, vector<Item*> argInv={}, Item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100);
    virtual string getType() override;
    int useEfficiency();
    void updateInventory();
};


class DamageComponent {
    int damage;
public:
    virtual int simulateDamage(Entity* entity);
    virtual int deal(Entity* entity);
};

void Player::attack(Entity* entity){
    entity->takeDamage(dmg);
}
int Player::menuPrompt(){
    utils::slowPrintPrompts({"what will you do?", "1. Attack With Firearm","2. Melee", "3. Inventory"});
    switch (utils::waitForInpt()){
        case '1':
            this->shootPrompt();
            break;
        case '2':
            this->meleePrompt();
            break;
        case '3':
            this->inventoryPrompt();
            break;
        default:
            utils::slowPrint({"That's not a thing you can do!"}, utils::WHITE, 10);
    }
};
void Player::inventoryPrompt(){};
void Player::meleePrompt(){};
void Player::shootPrompt(){};
void Entity::dealDamage(int amount, Entity* entity){
    entity->takeDamage(amount);
}

void Human::use(Item* item){

}

void Human::useWeapon(Weapon* weapon, Entity* entity){
    
}

void Human::useThrowable(Throwable* throwable, Entity* entity){

}

void Human::removeFromInv(Item* item){
    //remove pointer from inv, call delete for item.
    auto ptr = find(inventory.begin(), inventory.end(), item);
    if (ptr == inventory.end()){
        cout << "tried to remove an item from inventory that doesn't exist" << endl;
    }
    else {
        inventory.erase(ptr);
        delete item; //! find out if this releases memory
    }
}

string Entity::getname(){
    return name;
}

void Human::consumeConsumable(Item* consumable){
    if (consumable->getType() != "Consumable"){
        cout << "consume function given a non consumable item\n";
        return;
    }
    if (find(inventory.begin(), inventory.end(), consumable) == inventory.end()){
        cout << "no such item\n";
        return;
    }
    Consumable* consptr = dynamic_cast<Consumable*>(consumable);
    consptr->apply(this);
    inventory.erase(find(inventory.begin(), inventory.end(), consumable));
}
void Item::putInInv(Human* human){
    owner = human;
    human->takeInInv(this);
}

void Human::useConsumable(Consumable* item){
    item->apply(this);
    this->removeFromInv(item);
};
void Human::takeInInv(Item* item){
    inventory.push_back(item);
    //: what happens when you buy it from the shop/get it from loop:
    //: item's put in inventory function gets called, which in turn calls the human's take in inventory function. at the end of all that the item knows who owns it and the human knows that it's in their inventory.
}

void Consumable::update(){
    if (uses_left == 0){
        //remove from inventory, then remove object from memory
        //it can only be in one inventory so it should have a pointer to that inventory/just the entity maybe?
        //use action should call the use action of the entity attached
    }
}

Item::Item(string argName, int argU_Limit, int argU_Left, int argSize)
    :name(argName), use_limit(argU_Limit), uses_left(argU_Left), size(argSize){};

void Item::setName(string argName){name = argName;}

string Item::getType(){
        return "Item";
    }

int Item::getUseLimit(){return use_limit;}

int Item::getUsesLeft(){return uses_left;}

void Item::decrementUsesLeft(int num){uses_left-= num;}



Weapon::Weapon(string argName, MOD argMod, int argDMG, int argSize)
    :Item(argName, INFINITE, INFINITE, argSize), modifier(argMod), dmg(argDMG){};

//tbi
void Weapon::attack(Entity*){};
 
string Weapon::getType(){
    return "Weapon";
}

int ValuedComponent::usePercent() {
    return value * 100 / max_value;
}

string ValuedComponent::getType() {
    return "ValuedComponent";
}

void ValuedComponent::setVal(int val) {
    value = val;
}

int ValuedComponent::getVal() {
    return value;
}

int ValuedComponent::getMaxVal() {
    return max_value;
}


Stat::HealthComponent::HealthComponent(int v, int mv) {
    if (mv == -1) {
        max_value = v;
    } else {
        max_value = mv;
    }
    value = v;
}

string Stat::HealthComponent::getType() {
    return "HealthComponent";
}

Stat::StaminaComponent::StaminaComponent(int v, int mv) {
    if (mv == -1) {
        max_value = v;
    } else {
        max_value = mv;
    }
    value = v;
}

string Stat::StaminaComponent::getType(){
    return "StaminaComponent";
}



Consumable::Consumable(string name, int use_limit, int uses_left, vector<ValuedComponent*> VCs, int size)
: Item(name, use_limit, uses_left, size), valueComponents(VCs) {}

void Consumable::addVC(ValuedComponent* vc) {
    valueComponents.push_back(vc);
}

string Consumable::getType() {
    return "Consumable";
}

vector<ValuedComponent*>& Consumable::getValueComponents() {
    return valueComponents;
}

void Consumable::apply(Entity* entity) {
    for (ValuedComponent* v : valueComponents) {    
        if (auto vc = dynamic_cast<Stat::HealthComponent*>(v)){
            entity->heal(vc->getVal());
        }
        else if (auto vc = dynamic_cast<Stat::StaminaComponent*>(v)){
            entity->increaseStamina(vc->getVal());
        }
    }
}



string Throwable::getType() {
    return "Throwable";
}

Entity::Entity() : name(""), age(0), gender(""), lvl(1), hp(100), max_hp(100), dmg(10), sta(100), max_sta(100) {}

Entity::Entity(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, int argSTA)
: name(argName), age(argAge), gender(argGender), lvl(argLVL), hp(argHP), max_hp(argHP), dmg(argDMG), sta(argSTA), max_sta(argSTA) {}

string Entity::getType() {
    return "Entity";
}

bool Entity::isAlive() {
    return hp > 0;
}

int Entity::getHp() {
    return hp;
}

int Entity::getSta() {
    return sta;
}

int Entity::getHpMax() {
    return max_hp;
}

int Entity::getStaMax() {
    return max_sta;
}

int Entity::getLVL() {
    return lvl;
}

int Entity::getDMG() {
    return dmg;
}

void Entity::heal(int amount) {
    hp = min(max_hp, hp + amount);
}

void Entity::increaseStamina(int amount) {
    sta = min(max_sta, sta + amount);
}

int Entity::calculateDmg(int damage) {
    return damage;
}

void Entity::takeDamage(int damage) {
    hp -= calculateDmg(damage);
}

int Entity::hpFullPercent() {
    if (max_hp < 1) return -1;
    return (hp * 100) / max_hp;
}

int Entity::staminaFullPercent() {
    if (max_sta < 1) return -1;
    return (sta * 100) / max_sta;
}

void Entity::consumeComponent(ValuedComponent* vc) {
    string type = vc->getType();
    if (type == "HealthComponent"){
        this->heal(vc->getVal());
    }
    else if (type == "StaminaComponent"){
        this->increaseStamina(vc->getVal());
    }
}

Human::Human(string argName, int argAge, string argGender, vector<Item*> argInv, Item* argItemAtHandPTR, int argLVL, int argHP, int argDMG, int argSTA)
    : Entity(argName, argAge, argGender, argLVL, argHP, argDMG, argSTA), item_at_hand(argItemAtHandPTR), inventory(argInv) {}

string Human::getType() {
    return "Human";
}

string Human::getname() {
    return name;
}

vector<Item*> Human::getInv() {
    return inventory;
}

vector<Consumable*> Human::getConsumablesInv(){
    vector<Consumable*> csvector;
    for (Item* iptr: inventory){
        if (iptr->getType() == "Consumable"){
            Consumable* cp = dynamic_cast<Consumable*>(iptr);
            csvector.push_back(cp);
        }
    }
    return csvector;
}



Player::Player(string argName, int argAge, string argGender, vector<Item*> argInv, Item* argItemAtHandPTR, int argLVL, int argHP, int argDMG, int argSTA)
    : Human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argSTA) {}

string Player::getType() {
    return "Player";
}

void Enemy::attack(Player* player) {
    player->takeDamage(dmg);
}

string Enemy::getType() {
    return "Enemy";
}



HumanEnemy::HumanEnemy(string argName, int argAge, string argGender, vector<Item*> argInv, Item* argItemAtHandPTR, int argLVL, int argHP, int argDMG, int argSTA)
: Human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argSTA) {}

string HumanEnemy::getType() {
    return "HumanEnemy";
}

int HumanEnemy::useEfficiency() {
    
    return 0; // Placeholder return
}

void HumanEnemy::updateInventory() {
    for (auto& item : inventory) {
        if (item->getType() == "Consumable") {
            Consumable* conptr = dynamic_cast<Consumable*>(item);
            if (conptr) {
                for (ValuedComponent* vc : conptr->getValueComponents()) {
                    
                }
            }
        }
    }
}


int DamageComponent::simulateDamage(Entity* entity) {
    return entity->calculateDmg(damage);
}

int DamageComponent::deal(Entity* entity) {
    // Implementation
    return 0; // Placeholder return
}
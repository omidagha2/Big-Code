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
    Item(string argName, int argU_Limit, int argU_Left, int argSize=1);   string getname(){return name;};
    void setName(string argName);

    virtual string getType();

    int getUseLimit();
    int getUsesLeft();
    void decrementUsesLeft(int num=1);
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
    Weapon(string argName, MOD argMod, int argDMG, int argSize);
    
    virtual void attack(Entity*);
    virtual string getType();
};

class firearm: public Weapon{
    //takes pointer to a character's ammo box
};

class melee: public Weapon{

};



class ValuedComponent {
protected:
    int max_value;
    int value;
public:
    virtual int usePercent();
    virtual int getValue();
    virtual string getType();
    virtual void setVal(int val);
    virtual int getVal();
    virtual int getMaxVal();
};


struct Stat {
    class HealthComponent : public ValuedComponent {
    public:
        HealthComponent(int v, int mv = -1);
        virtual string getType() override;
    };

    class StaminaComponent : public ValuedComponent {
    public:
        StaminaComponent(int v, int mv = -1);
        virtual string getType() override;
    };
};


struct Damage_Type{
    
};


class Consumable: public Item {
    vector<ValuedComponent> valueComponents;
public: 
    Consumable(string name, int use_limit, int uses_left, vector<ValuedComponent> VCs={}, int size=1);
    void addVC(ValuedComponent vc);
    string getType();
    vector<ValuedComponent>* getValueComponents();
    void apply(Entity* entity);
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
    virtual void consumeComponent(ValuedComponent vc);
};


class Human: public Entity {
protected:
    Item* item_at_hand;
    vector<Item> inventory;

public:
    Human(string argName, int argAge, string argGender, vector<Item> argInv={}, Item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100);
    virtual string getType();
    string getname();
    vector<Item>* getInv();
};


class Player: public Human {
    // Assuming DamageComponent is correctly implemented elsewhere.
    friend class DamageComponent;

public:
    Player(string argName, int argAge, string argGender, vector<Item> argInv={}, Item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100);
    virtual string getType();
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
    HumanEnemy(string argName, int argAge, string argGender, vector<Item> argInv={}, Item* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100);
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

int ValuedComponent::getValue() {
    return value;
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

string Stat::StaminaComponent::getType() {
    return "StaminaComponent";
}



Consumable::Consumable(string name, int use_limit, int uses_left, vector<ValuedComponent> VCs, int size)
: Item(name, use_limit, uses_left, size), valueComponents(VCs) {}

void Consumable::addVC(ValuedComponent vc) {
    valueComponents.push_back(vc);
}

string Consumable::getType() {
    return "Consumable";
}

vector<ValuedComponent>* Consumable::getValueComponents() {
    return &valueComponents;
}

void Consumable::apply(Entity* entity) {
    for (ValuedComponent v : valueComponents) {
        entity->consumeComponent(v);
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

void Entity::consumeComponent(ValuedComponent vc) {
    string type = vc.getType();
    if (type == "HealthComponent"){
        this->heal(vc.getValue());
    }
    else if (type == "StaminaComponent"){
        this->increaseStamina(vc.getValue());
    }
}




Human::Human(string argName, int argAge, string argGender, vector<Item> argInv, Item* argItemAtHandPTR, int argLVL, int argHP, int argDMG, int argSTA)
    : Entity(argName, argAge, argGender, argLVL, argHP, argDMG, argSTA), item_at_hand(argItemAtHandPTR), inventory(argInv) {}

string Human::getType() {
    return "Human";
}

string Human::getname() {
    return name;
}

vector<Item>* Human::getInv() {
    return &inventory;
}




Player::Player(string argName, int argAge, string argGender, vector<Item> argInv, Item* argItemAtHandPTR, int argLVL, int argHP, int argDMG, int argSTA)
    : Human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argSTA) {}

string Player::getType() {
    return "Player";
}




void Enemy::attack(Player* player) {
    // Implementation
}

string Enemy::getType() {
    return "Enemy";
}



HumanEnemy::HumanEnemy(string argName, int argAge, string argGender, vector<Item> argInv, Item* argItemAtHandPTR, int argLVL, int argHP, int argDMG, int argSTA)
: Human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argSTA) {}

string HumanEnemy::getType() {
    return "HumanEnemy";
}

int HumanEnemy::useEfficiency() {
    // Implementation
    return 0; // Placeholder return
}

void HumanEnemy::updateInventory() {
    for (auto& item : inventory) {
        if (item.getType() == "Consumable") {
            Consumable* conptr = dynamic_cast<Consumable*>(&item);
            if (conptr) {
                for (ValuedComponent& vc : *conptr->getValueComponents()) {
                    // Implementation
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
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <windows.h>
#include "items.hpp"
#include <conio.h>
using namespace std;



const int SP_CHAR_DELAY_DEFAULT = 15;
const int SP_PAR_DELAY_DEFAULT = 800;



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
    char waitForInpt(){
        int i;
        while(true){
            if ((kbhit()) && (i = getch())){
                if (i != 0) return i;
            };
        }
    }
    void slowPrint(string prompt, Color color=WHITE, double char_delay_ms=SP_CHAR_DELAY_DEFAULT){
        for (char c: prompt){
            cout << c;
            Sleep(char_delay_ms);
        }
    }
    int slowPrintPrompts(vector<string> prompts, vector<int> input_vector={}, double char_delay_ms=SP_CHAR_DELAY_DEFAULT, double sentence_delay_ms=SP_PAR_DELAY_DEFAULT, string sentence_sep = "\n", Color color=WHITE){
        int i;
        for (int i = 0; i < prompts.size(); i++){    
            for (char c: prompts[i]){
                if ((kbhit())&&(i = getch())){
                    if (find(input_vector.begin(), input_vector.end(), i) != input_vector.end()) return i;
                };
                cout << c;
                Sleep(char_delay_ms);
            }
            Sleep(sentence_delay_ms);
            if (i != prompts.size()) cout << sentence_sep;
        }
        if (input_vector.size() > 0){
            while (true){
                int input = waitForInpt();
                if (find(input_vector.begin(), input_vector.end(), input) == input_vector.end()){
                    
                }
                else return input;
            }
        }
    }
    void cls(){
        system("cls");
    }
    void cll() {
    }
    int promptUser(vector<string> choices, vector<string> prompt ={}, vector<vector<string>> choice_descriptions = {}, bool prompt_first = false){  
        int choice = 0;

        while(true){
            cls();
            int max_choice_length = 0;
            for (int i = 0; i < choices.size(); i++){
                if (choices[i].length() > max_choice_length) max_choice_length = choices[i].length();
                if (i == choice) cout << '>';
                cout << i+1 << ". " << choices[i] << endl;
            }
            for (int i = 0; i < max_choice_length*1.2; i++) cout << '~';
            cout << endl;
            int ud = slowPrintPrompts(prompt, {72, 80, 13});
            if (ud == 72){
                choice = max(choice - 1, 0);
            }
            else if (ud == 80){
                choice = min(choice + 1, int(choices.size()) - 1);
            }
            else if (ud == 13){
                return choice + 1;
            }
        }
    }
    // int promptUserPF(vector<string> choices, vector<string> description){
        
    // }
}

class Item{
    friend class HumanEnemy;
protected:
    Human* owner;
    string name;
    string description;

public:
    virtual void putInInv(Human* human);


    string getDesc();
    void setDesc(string desc);
    Item(string argName);
    string getname(){return name;};
    virtual string getType();
    void setName(string argName);
};


class Weapon: public Item{
protected:
    vector<DamageComponent> dcvector;
    int basedmg;

public:
    virtual void attack(Entity*);
    virtual int estimateDamage(Entity* entity);

    virtual vector<DamageComponent> getDcVector();
    Weapon(string argName, vector<DamageComponent> dcs, int argDMG, Human* argOwner);
    virtual string getType();
};

class Firearm: public Weapon{
    
};

class Melee: public Weapon{

};

class ValuedComponent {
protected:
    int max_value;
public:

    
    virtual string getType();
    virtual int getMaxVal();
};


struct Stat {
    class HealthComponent : public ValuedComponent {
    public:
        HealthComponent(int v);
        string getType() override;
    };

    class StaminaComponent : public ValuedComponent {
    public:
        StaminaComponent(int v);
        string getType() override;
    };
};

//tbi
struct Damage_Type{
    
};


class Consumable: public Item {
    vector<ValuedComponent*> valueComponents;
public: 
    Consumable(string name, vector<ValuedComponent*> VCs={});
    string getType();
    vector<ValuedComponent*>& getValueComponents();
    //switch out the inheritance just for types and the other thing


    void addVC(ValuedComponent* vc);
    void apply(Entity* entity);
};

class Throwable: public Weapon{
public:
    Throwable(string argName, vector<DamageComponent> dcs, int argDMG, Human* argOwner);
    string getType();
};


class Entity {
    // Assume friend classes and enum are declared here
protected:
    string name;
    int age;
    string weaknesses; //a string that represents weakness array. ice being in the stirng means the entity is weak against ice, etc.
    string withstands; //same thing as weaknesses stirng
    string gender; 
    int lvl;
    int hp;
    int max_hp;
    int dmg;
    int sta;
    int max_sta;
public:
    virtual bool isAlive();
    void heal(int amount);
    void increaseStamina(int amount);
    int healAmount(int amount);
    int increaseStaminaAmount(int amount);
    int hpFullPercent();
    int staminaFullPercent();
    virtual int calculateDmg(DamageComponent);
    void takeDamage(int damage);
    virtual void dealDamage(int amount, Entity* entity);
    virtual void consumeComponent(ValuedComponent *vc);
    virtual int calculateDmgWpn(Weapon* weapon);
    virtual void getAttacked(Weapon* weapon);
    virtual void die()=0;

    Entity();
    Entity(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, int argSTA);
    virtual string getType();
    int getHp();
    string getname();
    int getSta();
    int getHpMax();
    int getStaMax();
    int getLVL();
    int getDMG();
    void takeIntDamage(int);
};


class Human: public Entity {
protected:
    Weapon* item_at_hand;
    vector<Item*> inventory;
    int combat_tokens;
public:
    virtual void attackWith(Weapon* weapon, Entity* entity)=0;
    virtual void use(Item*);
    virtual void useFirearm(Firearm*, Entity*);
    virtual void useMelee(Melee*, Entity*);
    virtual void useThrowable(Throwable*, Entity*);
    virtual void useConsumable(Consumable*);
    virtual void takeInInv(Item* item);
    virtual void consumeConsumable(Item* consumable);
    virtual void removeFromInv(Item* item);
    int effectiveValue(ValuedComponent* vcptr);
    vector<string> getItemNames();


    Human(string argName, int argAge, string argGender, vector<Item*> argInv={}, Weapon* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100);
    virtual string getType();
    string getname();
    vector<Item*> getInv();
    vector<Consumable*> getConsumablesInv();
};


class Player: public Human {

public:
    int atkBar();
    virtual void attack(Entity* entity);
    int CombatMenuPrompt();
    void inventoryPrompt(); //throwable, consumable, ammo_box, needle, ...
    void meleePrompt();
    void shootPrompt();
    void attackWithMelee(Weapon* weapon, Entity* entity);


    Player(string argName, int argAge, string argGender, vector<Item*> argInv={}, Weapon* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100);
    virtual string getType();
};


class Enemy : public Entity {
public:
    virtual void attack(Player* player)=0;


    virtual string getType() override;
};
class DamageComponent{
    enum class type{
        regular,
        ice,
        fire,
        explosion, 
        peanut_butter
    };
    type dmgType;
    string special;
    int damage;
public:
    virtual int simulateDamage(Entity* entity);
    virtual int deal(Entity* entity);//remove


    string getTypeStr();
    int getDmg();
};
class Zombie: public Enemy{
    enum type{
        CommonHusk,
        //tbi
    };
    DamageComponent dmgcmp;
public:
    void attack(Player* player) override;
};

class HumanEnemy : public Human, public Enemy {
    string dialogue;
    Player* target; 
public:
    int usePercentVC(ValuedComponent* vcptr);
    int usePercentConsumable(Consumable* cons);
    void updateInventory();


    HumanEnemy(string argName, int argAge, string argGender, vector<Item*> argInv={}, Weapon* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100);
    virtual string getType() override;
    void attack(Player* player) override;
};

vector<string> Human::getItemNames(){
    vector<string> names = {};
    for (Item* i: inventory){
        names.push_back(i->getname());
    }
    return names;
}

string Item::getDesc(){
    return description;
}

void Item::setDesc(string desc){
    description = desc;
}

void Player::attackWithMelee(Weapon* weapon, Entity* entity){
    entity->getAttacked(weapon);
    entity->takeIntDamage(dmg);
    utils::slowPrintPrompts({"You dealt ", to_string(entity->calculateDmgWpn(weapon)), " points of damage to ", entity->getname()});
    //
}
//maybe switch out the void stuff with stirngs that return the prompts for the attack. or don't

int DamageComponent::getDmg(){
    return damage;
}

vector<DamageComponent> Weapon::getDcVector(){
    return dcvector;
}

void Entity::getAttacked(Weapon* weapon){
    if (calculateDmgWpn(weapon) >= hp) this->die();
    else{
        hp -= calculateDmgWpn(weapon);
    }
}

int Entity::calculateDmgWpn(Weapon* weapon){
    int sum = 0;
    for (auto dc: weapon->getDcVector()){
        sum += calculateDmg(dc);
    }
    return sum;
}

void HumanEnemy::attack(Player* player){
    player->getAttacked(item_at_hand);
}

Throwable::Throwable(string argName, vector<DamageComponent> dcs, int argDMG, Human* argOwner)
    :Weapon(argName, dcs, argDMG, argOwner){};

void Zombie::attack(Player* player){
    player->takeDamage(dmg);
}

int Weapon::estimateDamage(Entity* entity){
    int sum = 0;
    for (auto dc: dcvector){
        sum += entity->calculateDmg(dc);
    }
    return sum;
};

string DamageComponent::getTypeStr(){
    switch (dmgType){
        case type::regular:
        return "regular";
        case type::ice:
        return "ice";
        case type::fire:
        return "fire";
        case type::explosion:
        return "explosion";
        case type::peanut_butter:
        return "peanut";
    }
}

void Player::attack(Entity* entity){
    entity->getAttacked(item_at_hand);
}

int Player::CombatMenuPrompt(){
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
//tbitbitbi
void Player::inventoryPrompt(){};
void Player::meleePrompt(){};
void Player::shootPrompt(){};
void Entity::dealDamage(int amount, Entity* entity){
    entity->takeDamage(amount);
}
void Entity::takeIntDamage(int amount){
    hp = max(hp - amount, 0);
}
//TBITBITBITBIBT(?)
void Human::use(Item* item){

}

void Human::useFirearm(Firearm* weapon, Entity* entity){
    
}
void Human::useMelee(Melee* weapon, Entity* entity){

};

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



Item::Item(string argName)
    :name(argName){};

void Item::setName(string argName){name = argName;}

string Item::getType(){
    return "Item";
}

Weapon::Weapon(string argName, vector<DamageComponent> argMod, int argDMG, Human* argOwner)
    :Item(argName), dcvector(argMod), basedmg(argDMG){owner = argOwner;};

//tbi
void Weapon::attack(Entity*){};
 
string Weapon::getType(){
    return "Weapon";
}

string ValuedComponent::getType() {
    return "ValuedComponent";
}


int ValuedComponent::getMaxVal() {
    return max_value;
}


Stat::HealthComponent::HealthComponent(int v) {
    max_value = v;
}

string Stat::HealthComponent::getType() {
    return "HealthComponent";
}

Stat::StaminaComponent::StaminaComponent(int v) {
    max_value = v;
}

string Stat::StaminaComponent::getType(){
    return "StaminaComponent";
}



Consumable::Consumable(string name, vector<ValuedComponent*> VCs)
: Item(name), valueComponents(VCs) {}

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

int Entity::healAmount(int amount){
    return min(hp + amount, max_hp) - hp;
}

int Entity::increaseStaminaAmount(int amount){
    return min(hp + amount, max_hp) - hp;
}

void Entity::heal(int amount) {
    hp = min(max_hp, hp + amount);
}

void Entity::increaseStamina(int amount) {
    sta = min(max_sta, sta + amount);
}

int Entity::calculateDmg(DamageComponent dmgcmp) { //should take damage component in actually
    if (weaknesses.find(dmgcmp.getTypeStr()) != string::npos){
        return 1.5 * dmgcmp.getDmg();
    }
    else if (withstands.find(dmgcmp.getTypeStr()) != string::npos){
        return 0.75 * dmgcmp.getDmg();
    }
}

void Entity::takeDamage(int damage) {
    hp -=damage;
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
        this->heal(vc->getMaxVal());
    }
    else if (type == "StaminaComponent"){
        this->increaseStamina(vc->getMaxVal());
    }
}

Human::Human(string argName, int argAge, string argGender, vector<Item*> argInv, Weapon* argItemAtHandPTR, int argLVL, int argHP, int argDMG, int argSTA)
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



Player::Player(string argName, int argAge, string argGender, vector<Item*> argInv, Weapon* argItemAtHandPTR, int argLVL, int argHP, int argDMG, int argSTA)
    : Human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argSTA) {}

string Player::getType() {
    return "Player";
}

string Enemy::getType() {
    return "Enemy";
}



HumanEnemy::HumanEnemy(string argName, int argAge, string argGender, vector<Item*> argInv, Weapon* argItemAtHandPTR, int argLVL, int argHP, int argDMG, int argSTA)
: Human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argSTA) {}

string HumanEnemy::getType() {
    return "HumanEnemy";
}


int HumanEnemy::usePercentVC(ValuedComponent* vcptr) {
    return effectiveValue(vcptr)/vcptr->getMaxVal();
}

int HumanEnemy::usePercentConsumable(Consumable* cons){
    vector<ValuedComponent*> vcs = cons->getValueComponents();
    int sum = 0;
    for (ValuedComponent* vc: vcs){
        sum += effectiveValue(vc);
    }
    return sum/vcs.size();
}
int Human::effectiveValue(ValuedComponent* vcptr){
    if (auto ptr = dynamic_cast<Stat::HealthComponent*>(vcptr)){
        return min(vcptr->getMaxVal() + hp, max_hp);
    }
    else if (auto ptr = dynamic_cast<Stat::StaminaComponent*>(vcptr)){
        return min(vcptr->getMaxVal() + sta, max_sta);
    }
}
//tbi? what even is this for?
void HumanEnemy::updateInventory() {
    for (auto& item : inventory) {
        if (item->getType() == "Consumable") {
            Consumable* conptr = dynamic_cast<Consumable*>(item);
            if (conptr) {
                for (ValuedComponent* vc : conptr->getValueComponents()) {
                    //?
                }
            }
        }
    }
}


int DamageComponent::simulateDamage(Entity* entity) {
    return entity->calculateDmg(*this);
}
//tbi?
int DamageComponent::deal(Entity* entity) {
    // Implementation
    return 0; // Placeholder return
}
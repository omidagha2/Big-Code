#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <windows.h>
#include "items.hpp"
#include <conio.h>
#include <random>
#include<time.h>
#include <map>
using namespace std;



const int SP_CHAR_DELAY_DEFAULT = 30;
const int SP_PAR_DELAY_DEFAULT = 800;



class DamageComponent;
class Entity;
class CombatController;
class Weapon;
class FireArm;
class Melee;
class HumanEnemy;
class Human;
class Player;
vector<string> nextPrompts={};
bool relics[7]={};
    /*
    0: makes melee vision horrible, maybe broken glasses.
    1: increase luck by 2.
    2: makes guns more accurate.
    3: increases fire damage (makes everyone weak against it) and decreases freeze damage (makes everyone strong against it)
    4: adds one to your tokens.
    5: increases any weapon's max ammo by 1.
    6: one that reduces luck but adds to your strength. for melee weapon build.
    */

// map<int, vector<string>> relicDescriptions{

// };



namespace relicDescriptions{

}

namespace utils{
    bool roll(int denom, int luck=0, int luck_mult=1){//has a chance of 1/(d-l*lm) to return true.
        int a = denom - luck*luck_mult;
        return a <= 0 ? true : rand() % a == 0;
    }
    enum Color{
        ORANGE,
        RED,
        GREEN,
        BLUE,
        WHITE

    };

    vector<string> popNextPrompts(){
        vector<string> temp = nextPrompts;
        nextPrompts.clear();
        return temp;
    }

    char waitForInpt(){
        int i;
        while(true){
            if ((kbhit()) && (i = getch())){
                if (i != 0) return i;
            };
        }
    }
    void slowPrint(string prompt, Color color=WHITE, double char_delay_ms=SP_CHAR_DELAY_DEFAULT){
        
    }
    int slowPrintPrompts(vector<string> prompts, vector<int> input_vector={}, char skip_key= '\\', double char_delay_ms=SP_CHAR_DELAY_DEFAULT, double sentence_delay_ms=SP_PAR_DELAY_DEFAULT, string sentence_sep = "\n", Color color=WHITE, int responsiveness=20){
        int p, chardel = char_delay_ms, sendel = sentence_delay_ms;
        if (find(input_vector.begin(), input_vector.end(), skip_key) != input_vector.end()) cout << "warning: this prompt accepts the skip key as input. it's likely the skip key won't work this time. ";
        for (int i = 0; i < prompts.size(); i++){
            for (char c: prompts[i]){
                if ((kbhit())&&(p = getch())){
                    if (find(input_vector.begin(), input_vector.end(), p) != input_vector.end()) return p;
                    if (p == skip_key){
                        char_delay_ms = 0;
                        sentence_delay_ms = 0;
                    }
                };
                if (c == '@'){
                    if (char_delay_ms == chardel){
                        char_delay_ms = 0;
                        sentence_delay_ms = 0;
                    }
                    else{
                        char_delay_ms = chardel;
                        sentence_delay_ms = sendel;
                    }
                }
                else if (c == '^'){
                    if (sentence_delay_ms == sendel){
                        sentence_delay_ms = 0;
                    }
                    else{
                        sentence_delay_ms = sendel;
                    }
                }
                else if (c == '~'){
                    if (sentence_sep == "\n") sentence_sep = "";
                    else sentence_sep = "\n";
                }
                else cout << c;
                Sleep(char_delay_ms);
            }
            if (i != prompts.size() - 1) {
                for (int j = 0; j < sentence_delay_ms/responsiveness; j++){
                    Sleep(responsiveness);
                    if (kbhit() && (p = getch())){
                        if (find(input_vector.begin(), input_vector.end(), p) != input_vector.end()) return p;
                        if (p == skip_key){
                            char_delay_ms = 0;
                            sentence_delay_ms = 0;
                        }
                    }
                }
                cout << sentence_sep;
            }
        }
        sentence_delay_ms = sendel;
        char_delay_ms = chardel;
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
    int promptUser(vector<string> choices, vector<string> preprompt, vector<vector<string>> choice_descriptions = {}, bool prompt_first = false){  
        
        slowPrintPrompts(preprompt);
        Sleep(500);
        cout << endl;


        int choice = 0;
        while(true){
            cls();
            slowPrintPrompts(preprompt, {}, '\\', 0, 0);
            cout << endl;
            for (int i = 0; i < 12; i++) cout << '~'; cout << endl;
            int max_choice_length = 10;
            for (int i = 0; i < choices.size(); i++){
                if (choices[i].length() > max_choice_length) max_choice_length = choices[i].length();
                if (i == choice) cout << '>';
                cout << i+1 << ". " << choices[i] << endl;
            }
            for (int i = 0; i < max_choice_length*1.2; i++) cout << '~';
            cout << endl;
            vector<string> desc;
            // if (choice_descriptions.size() == 1){
            //     //won't skip current prompt
            // }
            if (choice >= choice_descriptions.size()) desc = {""};
            else desc = choice_descriptions[choice];
            int ud = slowPrintPrompts(desc, {72, 80, 13});
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
}

class Item{
protected:
    Human* owner;
    string name;
    vector<string> description;
    int token_uses;

public:
    virtual void putInInv(Human* human);
    virtual void removeFromInv(Human* human);


    vector<string> getDesc();
    void setDesc(vector<string> desc);
    Item(string argName);
    Item(string argName, vector<string> desc, Human* argOwner=nullptr, int tu=1){
        name = argName;
        owner = argOwner;
        description = desc;
        token_uses = tu;
    }
    string getname(){return name;};
    virtual string getType();
    void setName(string argName);
    void setOwner(Human*);

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

class AmmoBox: public Item{
    public:
    void apply(FireArm*);
};

class FireArm: public Weapon{
    int max_ammo;
    int ammo;
    public:
    int getAmmo(){return ammo;}
    int getMaxAmmo(){return max_ammo;}
    int refillAmmo(int amount = -1){ammo = (amount == -1 ? max_ammo : min(max_ammo, ammo + amount));}
    int decreaseAmmo(int amount = 1){ammo = max(ammo - amount, 0);}
    FireArm(string argName, vector<DamageComponent> dcs, int argDMG, Human* argOwner, int ARGmax_ammo, int ARG_ammo);
};

class Melee: public Weapon{
//modifiers?
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

class Consumable: public Item {
    vector<ValuedComponent*> valueComponents;
    vector<DamageComponent> damageComponents;
public: 
    Consumable(string name, vector<ValuedComponent*> VCs, vector<DamageComponent> DCs={}, vector<string> desc = {}, Human* owner = nullptr, int tokenUses = 1);
    string getType();
    vector<ValuedComponent*>& getValueComponents();
    //switch out the inheritance just for types and the other thing


    void addVC(ValuedComponent* vc);
    void apply(Entity* entity);
};


class Entity {
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
    int luck;
    vector<string> prompts;
public:
    virtual bool isAlive();
    void heal(int amount);
    void increaseStamina(int amount);
    int healAmount(int amount);
    int increaseStaminaAmount(int amount);
    int hpFullPercent();
    int staminaFullPercent();
    virtual int calculateDmg(DamageComponent, double=1);
    void takeDamage(int damage);
    virtual void dealDamage(int amount, Entity* entity);
    virtual void consumeComponent(ValuedComponent *vc);
    virtual int calculateDmgWpn(Weapon* weapon, double mult=1);
    virtual void getAttacked(Weapon* weapon, double multiplier = 1);
    virtual void die();
    virtual void addweakness(string str){weaknesses.append(str);}
    virtual void addwithstand(string str){withstands.append(str);}

    string getRandomPrompt() {
        if (prompts.empty()) return "No prompts available.";
        return prompts[rand() % prompts.size()];
    }

    Entity();
    Entity(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, int argSTA, string withstandstr = "", string weaknessstr = "", vector<string> argPrompts = {})
        : name(argName), age(argAge), gender(argGender), lvl(argLVL), hp(argHP), max_hp(argHP), dmg(argDMG), sta(argSTA), prompts(argPrompts) {}
    virtual string getType();
    int getHp();
    string getname();
    int getSta();
    int getHpMax();
    int getStaMax();
    int getLVL();
    int getDMG();
    void takeIntDamage(int);
    void setluck(int l){luck = l;}
    int getluck(){return luck;}
};


class Human: public Entity {
protected:
    Weapon* item_at_hand;
    Weapon* melee_weapon;
    Weapon* firearm_weapon;
    vector<Item*> inventory;
    int max_combat_tokens;
    int combat_tokens;
public:
    virtual void attackWith(Weapon* weapon, Entity* entity);
    virtual void use(Item*);
    virtual void useFireArm(FireArm*, Entity*);
    virtual void useMelee(Melee*, Entity*);
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
    int getCombatTokens(){return combat_tokens;}
    int getMaxCombatTokens(){return max_combat_tokens;}
    void increaseMaxCombatTokens(int amount){max_combat_tokens += amount;}
    void setCombatTokens(int amount){combat_tokens = min(max_combat_tokens, amount);}
    void usetokens(int amount){setCombatTokens(max(0, combat_tokens - amount));}
    void setfirearm(Weapon* fa);
    Weapon* getFireArm();
    void setMelee(Weapon* fa);
    Weapon* getMelee();

    
};


class Player: public Human {
    vector<Item*> special_items_inventory; //won't fill up.
public:
    
    int atkBarGun(int offset, int length = 11, bool rawscore = false, bool showting = true, char crosshair = '^');
    int atkBarMelee(int offset);
    virtual void attack(Entity* entity);
    int CombatMenuPrompt(vector<string>);
    void inventoryPrompt(); //throwable, consumable, ammo_box, needle, ...
    void meleePrompt();
    void specialItemsPrompt();
    void shootPrompt();
    void attackWithMelee(Weapon* weapon, Entity* entity);
    void attackWithGun(Weapon* weapon, Entity* entity);
    void addSpecialItem(Item* item);
    vector<Item*> getSpecialItems();
    void removeSpecialItem(Item*);
    void updateRelics();
    void resetNextPrompts(){nextPrompts = {};}
    void addtoNextPrompts(string np){nextPrompts.push_back(np);}
    vector<string> getNextPrompts(){return nextPrompts;}
    virtual ~Player(){};

    Player(string argName, int argAge, string argGender, vector<Item*> argInv={}, Weapon* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100);
    virtual string getType();
};


class Enemy : public Entity {
public:
    Enemy(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, int argSTA, vector<string> argPrompts = {})
    :Entity(argName, argAge, argGender, argLVL, argHP, argDMG, argSTA, "", "", argPrompts) {}
    Enemy(){};
    virtual void attack(Player* player)=0;


    virtual string getType() override;
};
class DamageComponent{
public:
    enum class TYPE{
        regular,
        ice,
        fire,
        explosion, 
        peanut_butter
    };
private:
    TYPE dmgType;
    int damage;
public:
    virtual int simulateDamage(Entity* entity);
    virtual int deal(Entity* entity);//remove


    string getTypeStr();
    int getDmg();
    DamageComponent(int dmg, TYPE type = TYPE::regular);
    DamageComponent(){};
};
class Zombie: public Enemy{
    enum TYPE{
        CommonHusk,
        //tbi
    };
    TYPE type;
    DamageComponent dmgcmp;
public:
    Zombie(string argName, int argAge, string argGender, int argLVL = 0, int argHP = 20, int argDMG = 1, int argSTA = 20, vector<string> argPrompts = {})
        : Enemy(argName, argAge, argGender, argLVL, argHP, argDMG, argSTA, argPrompts) {}

    void attack(Player* player) override;
};

class HumanEnemy : public Human, public Enemy {
    enum State{
        CalcBestWeapon,
        Entry,
        DanerouslyLowHp,
        KindaLowHp,
        HpFine,
        AreThereTokens,
        Attack
    };
    vector<string> state_prompts;
    State current_state;
    string dialogue;
    Player* target; 
public:
    void setCurrentState(State state){current_state = state;}
    State getCurrentState(){return current_state;}
    
    vector<string> getStatePrompts(){return state_prompts;}
    void setStatePrompts(vector<string> spv){state_prompts = spv;}
    int usePercentVC(ValuedComponent* vcptr);
    int usePercentConsumable(Consumable* cons);
    void updateInventory();
    virtual Weapon* getItemAtHand();

    HumanEnemy(string argName, int argAge, string argGender, vector<string> stateprs, vector<Item*> argInv={}, Weapon* argItemAtHandPTR=nullptr, int argLVL=1, int argHP=100, int argDMG=1, int argSTA=100);
    virtual string getType() override;
    void attack(Player* player) override;
};

int Player::atkBarGun(int offset, int length, bool rawscore, bool showthing, char crosshair){
    int score = 1;
    string backspc = "\b \b\b";
    backspc.push_back(crosshair);
    string forward = "\b ";
    forward.push_back(crosshair);
    length = max(length, 11);
    int way = 1;
    if (showthing){
        for (int i = 0; i < (length - 7)/2; i++){
            cout << '~';
        }
        cout << char(176) << char(177) << char(177) << char(178) << char(177) << char(177) << char(176);
        for (int i = 0; i < (length - 7)/2; i++){
            cout << '~';
        }
        cout << endl;
    }
    /*  ░▒▒▓▒▒░  */
    while(true){
        for (int i = 0; i < 8; i++){
        Sleep(10);
            if (kbhit() && getch() == ' '){
                int n = ceil(length/2.0);
                // return (max(n - abs(n-score), 0));
                return (rawscore ? score : n - abs(n-score));
            }
        }
        if (score == length){
            way = -1;
        }
        else if (score == 1){
            way = 1;
        }
        score += way;
        cout << (way < 0 ? backspc : forward);
        // cout << (way < 0 ? "\b \b\b^" : "\b ^ ");
    }
}

int Player::atkBarMelee(int offset){
    int score = 0;
    int way = 1;
    if (relics[0]) cout << "~~~~" << char(176) << char(176) << char(176) << char(177) << char(177) << char(177) << char(178) << endl;
    else cout << '.' << ',' << '-' << char(169) << '~' << char(174) << char(22) << char(31) << char(254) << char(219) << char(178) << endl;
    return atkBarGun(offset, 11, true, false, '*');
}
DamageComponent::DamageComponent(int dmg, TYPE type){
    damage = dmg;
    dmgType = type;
};
Weapon* HumanEnemy::getItemAtHand(){
        return item_at_hand;
};

Consumable::Consumable(string name, vector<ValuedComponent*> VCs, vector<DamageComponent> DCs, vector<string> desc = {}, Human* owner = nullptr, int tokenUses = 1)
    : Item(name, desc, owner, tokenUses), valueComponents(VCs), damageComponents(DCs) {}

void Player::updateRelics(){
//based on special items available, change global variables. maybe just for the player. or maybe it's a singleton. idk.
    max_combat_tokens = 3 + relics[4];
}

void Item::removeFromInv(Human* human){
    human->removeFromInv(this);
    delete this;
}

void Player::addSpecialItem(Item* item){
    special_items_inventory.push_back(item);
    item->setOwner(this);
}

void Player::removeSpecialItem(Item* item){
    special_items_inventory.erase(find(special_items_inventory.begin(), special_items_inventory.end(), item));
    delete item;
}

void Item::setOwner(Human* human){
    owner = human;
}

vector<Item*> Player::getSpecialItems(){
    return special_items_inventory;
}

void Entity::die(){};//!
void Human::attackWith(Weapon* weapon, Entity* entity){};//!
vector<string> Human::getItemNames(){
    vector<string> names = {};
    for (Item* i: inventory){
        names.push_back(i->getname());
    }
    return names;
}

void AmmoBox::apply(FireArm* weapon){
    weapon->refillAmmo();
    nextPrompts.push_back("You refilled " + weapon->getname() + ".");
    owner->removeFromInv(this);
    delete this;
}

FireArm::FireArm(string argName, vector<DamageComponent> dcs, int argDMG, Human* argOwner, int ARGmax_ammo, int ARG_ammo)
:Weapon(argName, dcs, argDMG, argOwner){max_ammo = ARGmax_ammo; ammo = ARG_ammo == -1 ? ARGmax_ammo : ARG_ammo;};

vector<string> Item::getDesc(){
    return description;
}

void Item::setDesc(vector<string> desc){
    description = desc;
}

void Player::attackWithGun(Weapon* weapon, Entity* entity){
    entity->getAttacked(weapon);
    auto gunptr = dynamic_cast<FireArm*>(weapon);
    if (gunptr == nullptr) utils::slowPrint(weapon->getname() + " is not a gun!\n");
    else{
        entity->getAttacked(weapon);
    }
};

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

void Entity::getAttacked(Weapon* weapon, double multiplier){
    if (calculateDmgWpn(weapon, multiplier) >= hp) this->die();
    else{
        hp -= calculateDmgWpn(weapon, multiplier);
    }
}

int Entity::calculateDmgWpn(Weapon* weapon, double mult){
    int sum = 0;
    for (auto dc: weapon->getDcVector()){
        cout << dc.getDmg() << '"' << endl;
        sum += calculateDmg(dc, mult);
    }
    return sum;
}

void HumanEnemy::attack(Player* player){
    player->getAttacked(item_at_hand);
}


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
        case TYPE::regular:
        return "regular";
        case TYPE::ice:
        return "ice";
        case TYPE::fire:
        return "fire";
        case TYPE::explosion:
        return "explosion";
        case TYPE::peanut_butter:
        return "peanut";
    }
}

void Player::attack(Entity* entity){
    entity->getAttacked(item_at_hand);
}

int Player::CombatMenuPrompt(vector<string> combatPrompt){
    int choice = utils::promptUser({"use a gun", "use a melee weapon", "look for useful combat items", "look in your schoolbag's second zipper"}, combatPrompt);
    switch (choice){
        case 1:
        this->shootPrompt(); break;
        case 2:
        this->meleePrompt(); break;
        case 3:
        this->inventoryPrompt(); break;
        case 4:
        this->specialItemsPrompt(); break;
    }
};
//tbitbitbi
void Player::inventoryPrompt(){};
void Player::meleePrompt(){};
void Player::shootPrompt(){};
void Player::specialItemsPrompt(){

}
void Entity::dealDamage(int amount, Entity* entity){
    entity->takeIntDamage(amount);
}
void Entity::takeIntDamage(int amount){
    hp = max(hp - amount, 0);
}
//TBITBITBITBIBT(?)
void Human::use(Item* item){

}

void Human::useFireArm(FireArm* weapon, Entity* entity){
    
}
void Human::useMelee(Melee* weapon, Entity* entity){

};



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

void Human::setfirearm(Weapon* fa){
    firearm_weapon = fa;
}
Weapon* Human::getFireArm(){return firearm_weapon;}
void Human::setMelee(Weapon* mw){
    melee_weapon = mw;
}
Weapon* Human::getMelee(){
    return melee_weapon;
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

Entity::Entity() : name(""), age(0), gender(""), lvl(1), hp(100), max_hp(100), dmg(10), sta(100), max_sta(100) {}

// Entity::Entity(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, int argSTA, string strwith, string strweak)
// : name(argName), age(argAge), gender(argGender), lvl(argLVL), hp(argHP), max_hp(argHP), dmg(argDMG), sta(argSTA), max_sta(argSTA) {
//     withstands = strwith;
//     weaknesses = strweak;
// }

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

int Entity::calculateDmg(DamageComponent dmgcmp, double mult) { //should take damage component in actually
    if (weaknesses.find(dmgcmp.getTypeStr()) != string::npos){
        return 1.5 * dmgcmp.getDmg();
    }
    else if (withstands.find(dmgcmp.getTypeStr()) != string::npos){
        return 0.75 * dmgcmp.getDmg();
    }
    else return dmgcmp.getDmg();
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



HumanEnemy::HumanEnemy(string argName, int argAge, string argGender, vector<string> stateprs, vector<Item*> argInv, Weapon* argItemAtHandPTR, int argLVL, int argHP, int argDMG, int argSTA)
: Human(argName, argAge, argGender, argInv, argItemAtHandPTR, argLVL, argHP, argDMG, argSTA){state_prompts = stateprs;}

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
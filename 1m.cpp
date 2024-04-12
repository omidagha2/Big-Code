#include <string>
#include <vector>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <ctime>

using namespace std;

const int SKILLS_IMPLEMENTED = 2;
int useOfSkill = 0;


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
enum class BossSkills{
    FireRocks,
    SummonHorse,
    SelfHealing,
    Vanishing
};

enum class ZOmbieClasses{
    Juggernaut,
    Knight,
    Intelligent,
    Theif
    //maybe some more classes
};

enum class Behavior{
    Aggressive,
    Defensive,
    // some more behaviors TBD
};

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    string name;
    double price;
    int quantity;

    Item(string n, double p, int q) : name(n), price(p), quantity(q) {}
};

bool compareByName(const Item& a, const Item& b) {
    return a.name < b.name; // Sort by name in ascending order
}

class Store {
private:
    vector<Item> items;

public:
    Store() {
        items.emplace_back("Kalashnikov", 1000.0, 10);
        items.emplace_back("pistol", 500.0, 20);
        // ... Add other items ...
    }

    void print() {
        cout << "Items in store:" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "| Item Name     | Price ($) | Quantity |" << endl;
        cout << "-----------------------------------------" << endl;
        for (const auto& item : items) {
            cout << "| " << item.name << " | $" << item.price << " | " << item.quantity << " |" << endl;
        }
        cout << "-----------------------------------------" << endl;
    }

    void reduceQuantity(const string& itemName, int quantityToReduce) {
        for (auto& item : items) {
            if (item.name == itemName) {
                if (item.quantity >= quantityToReduce) {
                    item.quantity -= quantityToReduce;
                    cout << "Reduced " << quantityToReduce << " " << itemName << "(s) from the store." << endl;
                } else {
                    cout << "Insufficient quantity of " << itemName << " in the store." << endl;
                }
                return;
            }
        }
        cout << "Item not found in the store." << endl;
    }

    void sortItemsByName() {
        sort(items.begin(), items.end(), compareByName);
    }
};

int main() {
    Store myStore;
    myStore.sortItemsByName(); // Sort items by name
    myStore.print(); // Print sorted items
    myStore.reduceQuantity("pistol", 2); // Example of reducing quantity
    return 0;
}
 

class item{
protected:
    string name;
    int use_limit;
    int uses_left;
    int size;

public:
    item(string name, int argU_Limit, int argU_Left, int argSize){}
    string nameofIt(){ cin >> name; return name;}
    item(){}
};

class weapon: public item{
protected:
    MOD modifier;
    int dmg;

public:
    weapon(string name, MOD argMod, int argDMG, int argSize)
    :item("",infinite, infinite, argSize), modifier(argMod), dmg(argDMG) {

    }
};

class store:public item {
    vector<item> weapons;

public:
    store(): item("", 0, 0, 0){
        weapons.emplace_back("Kalashnikov",common, 10,1);
        weapons.emplace_back("pistol",common, 8,1);
        weapons.emplace_back("graneid",common, 10,1);
        weapons.emplace_back("sks",common, 20,1);
        weapons.emplace_back("m14",common, 15,1);
        weapons.emplace_back("knife",common, 5,1);


    }

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
    int coin;

public:
    virtual void attack(entity* x)=0;

    entity()=default;
    entity(string argName, int argAge, string argGender, int argLVL=1, int argHP=0, int argDMG=0, int argSTA=0)
    :name(argName), age(argAge), gender(argGender), lvl(argLVL), hp(argHP), dmg(argDMG), sta(argSTA){}
    string getName() const {return name;}
    int getLvl() const {return lvl;}
    int getDmg() const {return dmg;}
    int getSta() const {return sta;}
    int getHp() const {return hp;}
    void setHp(int newhp)
    {
        hp=newhp;
    }
    
};

class human: public entity{
protected:
    item item_at_hand;
    vector<vector<string>> inventory={{"weopons"},{"healer Items"},{"throwable Items"}};
    int skills[SKILLS_IMPLEMENTED];

public: 
    human(string argName, int argAge, string argGender, int argLVL=1, int argHP=0, int argDMG=0, int argSTA=0)
    : entity(argName, argAge, argGender, argLVL, argHP, argDMG, argSTA),item_at_hand("",0,0,0) {
        
    }
    human(){}
    virtual void attack(entity* x) {

    }
    item changeHeldItem(string pack) {
        item Item;
        for (int i = 0; i < 3; i++)
        {
            if (inventory[i][0]==pack)
            {
                for (int j = 0; j < inventory[i].size(); j++)
                {
                    cout << inventory[i][j] << ",,";

                }
                Item.nameofIt();
                item_at_hand=Item;
            }
            
        }
        
        return item_at_hand;
    }
    
};

class characters: public human{
    vector<human> chars;
public:
   
    characters() {
        // Directly initialize the characters in the constructor
        chars.emplace_back("Thalion", 20, "Male", 1, 100, 10, 10);
        chars.emplace_back("Eirwyn", 25, "Male", 1, 110, 20, 20);
        chars.emplace_back("Brondar", 20, "Male", 1, 120, 20, 30);
        chars.emplace_back("Mirelle", 20, "Female", 1, 150, 45, 35);
        chars.emplace_back("Kaelum", 20, "Male", 1, 200, 50, 50);
        chars.emplace_back("Seraphina", 20, "Female", 1, 190, 60, 45); 
        chars.emplace_back("Draxen", 20, "Male", 1, 105, 20, 25);
        chars.emplace_back("Arianya", 20, "Female", 1, 130, 10, 35);
        chars.emplace_back("Fenris", 20, "Male", 1, 300, 65, 40);
        chars.emplace_back("Lyrielle", 20, "Female", 1, 500, 100, 100);
    }
    human* choice()
    {
        int a = 0;
        cout << "\nChoose a character\n";
        displaychars();
        cin >> a;
        if (a >= 1 && a <= chars.size()) {
            return &chars[a-1];
        } else {
            cout << "Choose between 1-10" << " please...\n";
            return nullptr; // Return a null pointer if the input is invalid
        }
    }

    
    void displaychars(){
        cout << "you can choose..\n";
        for (int i = 0; i < chars.size(); i++)
        {
            cout << (i+1) << ". " << "Name: " << chars[i].getName() << endl << "Level: " << chars[i].getLvl() << endl;
            cout << "Damage: " << chars[i].getDmg() << endl << "Stamina: " << chars[i].getSta() << endl;
        }
        
    }

    void attack(entity* a,weapon* wepon) {
        a->hp-=

    }

    bool isDefeated() const {

        return hp <= 0;
    }

};


class humanEnemies :public human {
    vector<human> enemy;
public:
    humanEnemies() {
        enemy.emplace_back("Stenchurion", 20, "Male", 1, 100, 5, 15);
        enemy.emplace_back("Cannibelle", 20, "Female", 1, 100, 7, 10);
        enemy.emplace_back("Magmalice", 20, "Male", 1, 200, 15, 10);
        enemy.emplace_back("Salamarauder", 20, "Female", 1, 150, 10, 15);
        enemy.emplace_back("Bewarewolf", 20, "Male", 1, 100, 15, 10);
        enemy.emplace_back("Lunatick", 20, "Male", 1, 120, 20, 10);
    }
   
    void attack(entity* a) {

    }

    bool isDefeated() const {

        return hp <= 0;
    }

};
//////////////////
vector<string> randomNames(string& filename){

    ifstream file(filename);
    vector<string> names;
    string line;

    while (getline(file , line)){
        names.push_back(line);
    }

    file.close();
    return names;
}

string getRandomName(vector<string>& names){
    
    int index = rand() % names.size();
    return names[index];
}

string BossSkillsTostring(BossSkills skill){

    switch (skill){

        case(BossSkills::FireRocks):
            return "ThrowingObjects";
        case(BossSkills::SummonHorse):
            return "SummonHorse";
        case(BossSkills::SelfHealing):
            return "SelfHealing";
        case(BossSkills::Vanishing):
            return "Vanishing"; 
        default:
            return "Unknown";
    }
}
string BehaviorToString(Behavior pattern){

    switch (pattern){
        
        case(Behavior::Aggressive):
            return "Aggressive";
        case(Behavior::Defensive):
            return "Defensive";
        default:
            return "Uknown";
    }
}

string ZombieClassToString(ZOmbieClasses cls){

    switch (cls){
        
        case(ZOmbieClasses::Intelligent):
            return "Intelligent";
        case(ZOmbieClasses::Juggernaut):
            return "Juggernaut";
        case(ZOmbieClasses::Knight):
            return "Knight";
        case(ZOmbieClasses::Theif):
            return "Theif";
        default:
            return "Unknown";
    }
}



class Entity{

protected:

    string name , Gender;
    int age , hp , Sta , lvl;

public:

    Entity() = default;
    Entity(string& name , int age , string& gender , int hp , int stamina , int level) : name(name) , age(age) , Gender(gender) , hp(hp) , Sta(stamina) , lvl(level) {} 
    Entity(int hp , int stamina , int level) : hp(hp) , Sta(stamina) , lvl(level) {} 

    virtual void Attack(Entity& target) = 0;

    bool isDefeated() const {

        return hp <= 0;
    }

    void updateHP(int damage){

        hp -= damage;
        if (hp < 0){

            hp = 0;
        }
    }


    string getName() const {
        return name;
    }
    int getAge() const {
        return age;
    }
    string getGender() const {
        return Gender;
    }
    int getHP() const {
        return hp;
    }
    int getStamina() const {
        return Sta;
    }
    int getLevel() const {
        return lvl;
    }


};

class Player : public Entity{

public:

    Player(string& name , int age , string& gender , int hp , int stamina , int level) : Entity(name , age , gender , hp , stamina , level){}

    void Attack(Entity& target) override {

        // some code and story tellings
    }

};

class Enemy : public Entity{

protected:
    

    Behavior Pattern;
    int Damage , Defense , Stealth , Armor;

    STATE current_state;
    vector<STATE> available_states;

public:

    Enemy() = default;
    Enemy(string& name , int age , string gender , int hp , int stamina , int level ,Behavior pattern, int damage , int defense , int stealth , int armor) : 
    Entity(name , age , gender , hp , stamina , level) , Pattern(pattern) , Damage(damage) , Defense(defense) , Stealth(stealth) , Armor(armor) {}

    void Attack(Entity& target) override {

        // some code and story tellings
    }
    


    int getDamage() const {
        return Damage;
    }
    int getDefense() const {
        return Defense;
    }
    int getStealth() const {
        return Stealth;
    }
    int getArmor() const {
        return Armor;
    }
    Behavior getBehavior() const {
        return Pattern;
    }


};


class Zombie : public Enemy{

protected:

    ZOmbieClasses Cls;

public:
    
    Zombie() = default;
    Zombie(string& name , int age , string& gender , int hp , int stamina , int level , Behavior pattern, int damage , int defense , int stealth , int armor , ZOmbieClasses cls) : 
    Enemy(name , age , gender , hp , stamina , level , pattern , damage , defense , stealth ,  armor) , Cls(cls) {}

    void Attack(Entity& target) override {

        int damageTaken = getDamage();
        updateHP(damageTaken);
    }

    ZOmbieClasses getZombieCls() const {
        
        return Cls;
    }

    int calcZdmg();
    int calcZTakenDmg(int tkDmg);  
};


class HumanEnemy : public Player{

    // some code to initialize and etc.


};


class ZombieBoss : public Zombie{

private:

    BossSkills Skill;
public:
    
    ZombieBoss(string& name , int age , string& gender , int hp , int stamina , int level , Behavior pattern, int damage , int defense , int stealth , int armor , ZOmbieClasses cls , BossSkills skill) :
        Zombie(name , age , gender , hp , stamina , level , pattern , damage , defense , stealth ,  armor , cls) , Skill(skill) {}

    BossSkills getBossSkill() const{
        return Skill;
    }
    
    int calcBossDmg(int damg);
    int calcBossTakenDmg(int tkDmg);
    void Attack(Entity& target);

    void HealBoss(){
        hp = hp * 1.25;
    }
    int damageOfShadow(){
        return Damage * 1.1;
    } 

};

int ZombieBoss::calcBossDmg(int damg){    
    return damg;
}
int ZombieBoss::calcBossTakenDmg(int tkDmg){

    if (getBossSkill() == BossSkills::Vanishing){
                if (useOfSkill < 3){
                    useOfSkill += 1;
                }
                else{
                    tkDmg = 0;
                    cout << "Wow Wow , where did the Zombie go? Looks like it disapeared. Missed Shot =((" << endl;
                    useOfSkill = 0;
                }
            }

    return tkDmg; 
}
int Zombie::calcZdmg(){
    return getDamage();
}
int Zombie::calcZTakenDmg(int tkDmg){
    
    srand(time(nullptr));
    int randNum = rand() % 10;
    if (getZombieCls() == ZOmbieClasses::Theif){
    
        if (randNum < getStealth()){
            tkDmg *= 0.8; 
        }
    }
    if (getZombieCls() == ZOmbieClasses::Intelligent){
       
       if (randNum < getStealth()){
            tkDmg *= 0.75; 
        } 
    }

    return tkDmg;
}

void ZombieBoss::Attack(Entity& target){
    
    if (getBossSkill() == BossSkills::FireRocks){

            if (useOfSkill < 4){
                //return getDamage();
                useOfSkill += 1;
            }
            else{
                cout << "Ah oh, Looks like a fire rock is coming to you!!" << endl;
                // return severe Damage
                useOfSkill = 0;
            }
        }
        if (getBossSkill() == BossSkills::SummonHorse){

            if (useOfSkill < 4){
                //return getDamage();
                useOfSkill += 1;
            }
            else{
                cout << "Oh No!! The Zombie has unleashed its horse and its coming to you!!" << endl;
                // return severe Damage
                useOfSkill = 0;
            }
        }
        if (getBossSkill() == BossSkills::SelfHealing){

            if (useOfSkill < 4){
                useOfSkill += 1;
            }
            else{
                HealBoss();
                cout << "Wait, What! Did the Zombie just Heal itself? Yep, seems like it's an Intelligent one =))" << endl;
                useOfSkill = 0;
                int dm = damageOfShadow();
                //return getDamage();
            }
        }
        if (getBossSkill() == BossSkills::Vanishing){

            if (useOfSkill < 3){
                //return getDamage();
                useOfSkill += 1;
            }
            else{
                cout << "Wow Wow , where did the Zombie go? Looks like it disapeared. Missed Shot =((" << endl;
                useOfSkill = 0;
            }
        }
    }

class ZombieFactory : public Zombie{

private:

    static Behavior generateBehavior(){
        int randNum = rand() % 2;
        Behavior pattern;

        if (randNum == 0) {
            
            pattern = Behavior::Aggressive;
        } 
        else if (randNum == 1) {
           
            pattern = Behavior::Defensive;
        }

        return pattern;
    }

    static ZOmbieClasses generateZombieCls(){
        int randNum = rand() % 4;
        ZOmbieClasses cls;

        if (randNum == 0) {
            cls = ZOmbieClasses::Juggernaut;
        }
        if (randNum == 1) {
            cls = ZOmbieClasses::Knight;
        }
        if (randNum == 2) {
            return ZOmbieClasses::Intelligent;
        }
        if (randNum == 3) {
            cls = ZOmbieClasses::Theif;
        }

        return cls;
    }

    static BossSkills generateBossSkill(ZOmbieClasses cls){

        BossSkills skill;
        if (cls == ZOmbieClasses::Intelligent){
            skill = BossSkills::SelfHealing;
        }
        if (cls == ZOmbieClasses::Juggernaut){
            skill = BossSkills::FireRocks;
        }
        if (cls == ZOmbieClasses::Knight){
            skill = BossSkills::SummonHorse;
        }
        if (cls == ZOmbieClasses::Theif){
            skill = BossSkills::Vanishing;
        }
        return skill;
    }

    static int generateHP(int PlayerHP , Behavior pattern , ZOmbieClasses cls , int RegOrBoss){
        
        int ZHP;
        if (RegOrBoss == 0){
            if (cls == ZOmbieClasses::Juggernaut){            
                if (pattern == Behavior::Defensive){
                    ZHP = PlayerHP + 10;
                }
                if (pattern == Behavior::Aggressive){
                    ZHP = PlayerHP + 5;
                }
            }
            if (cls == ZOmbieClasses::Knight){            
                if (pattern == Behavior::Defensive){
                    ZHP = PlayerHP + 5;
                }
                if (pattern == Behavior::Aggressive){
                    ZHP = PlayerHP;
                }
            }
            if (cls == ZOmbieClasses::Intelligent){            
                if (pattern == Behavior::Defensive){
                    ZHP = PlayerHP;
                }
                if (pattern == Behavior::Aggressive){
                    ZHP = PlayerHP - 5;
                }
            }
            if (cls == ZOmbieClasses::Theif){            
                if (pattern == Behavior::Defensive){
                    ZHP = PlayerHP - 5;
                }
                if (pattern == Behavior::Aggressive){
                    ZHP = PlayerHP - 10;
                }
            }
        }

        else{ // generating for the Zombie boss

            if (cls == ZOmbieClasses::Juggernaut){            
                if (pattern == Behavior::Defensive){
                    ZHP = PlayerHP + 35;
                }
                if (pattern == Behavior::Aggressive){
                    ZHP = PlayerHP + 30;
                }
            }
            if (cls == ZOmbieClasses::Knight){            
                if (pattern == Behavior::Defensive){
                    ZHP = PlayerHP + 30;
                }
                if (pattern == Behavior::Aggressive){
                    ZHP = PlayerHP + 25;
                }
            }
            if (cls == ZOmbieClasses::Intelligent){            
                if (pattern == Behavior::Defensive){
                    ZHP = PlayerHP + 25;
                }
                if (pattern == Behavior::Aggressive){
                    ZHP = PlayerHP + 20;
                }
            }
            if (cls == ZOmbieClasses::Theif){            
                if (pattern == Behavior::Defensive){
                    ZHP = PlayerHP + 20;
                }
                if (pattern == Behavior::Aggressive){
                    ZHP = PlayerHP + 20;
                }
            }  
        }
        return ZHP;    
    }

    static int generateStamina(int PlayerStm , Behavior pattern , ZOmbieClasses cls , int RegOrBoss){
        int ZStm;
        if (RegOrBoss == 0){
            if (cls == ZOmbieClasses::Juggernaut){            
                if (pattern == Behavior::Defensive){
                    ZStm = PlayerStm * 1.1;
                }
                if (pattern == Behavior::Aggressive){
                    ZStm = PlayerStm * 0.9;
                }
            }
            if (cls == ZOmbieClasses::Knight){            
                if (pattern == Behavior::Defensive){
                    ZStm = PlayerStm * 1.05;
                }
                if (pattern == Behavior::Aggressive){
                    ZStm = PlayerStm * 0.85;
                }
            }
            if (cls == ZOmbieClasses::Intelligent){            
                if (pattern == Behavior::Defensive){
                    ZStm = PlayerStm * 1.1;
                }
                if (pattern == Behavior::Aggressive){
                    ZStm = PlayerStm * 0.9;
                }
            }
            if (cls == ZOmbieClasses::Theif){            
                if (pattern == Behavior::Defensive){
                    ZStm = PlayerStm * 1.05;
                }
                if (pattern == Behavior::Aggressive){
                    ZStm = PlayerStm * 0.9;
                }
            }
        }

        else{ // generating for the Zombie boss
            if (cls == ZOmbieClasses::Juggernaut){            
                if (pattern == Behavior::Defensive){
                    ZStm = PlayerStm * 1.4;
                }
                if (pattern == Behavior::Aggressive){
                    ZStm = PlayerStm * 1.35;
                }
            }
            if (cls == ZOmbieClasses::Knight){            
                if (pattern == Behavior::Defensive){
                    ZStm = PlayerStm * 1.35;
                }
                if (pattern == Behavior::Aggressive){
                    ZStm = PlayerStm * 1.3;
                }
            }
            if (cls == ZOmbieClasses::Intelligent){            
                if (pattern == Behavior::Defensive){
                    ZStm = PlayerStm * 1.3;
                }
                if (pattern == Behavior::Aggressive){
                    ZStm = PlayerStm * 1.25;
                }
            }
            if (cls == ZOmbieClasses::Theif){            
                if (pattern == Behavior::Defensive){
                    ZStm = PlayerStm * 1.25;
                }
                if (pattern == Behavior::Aggressive){
                    ZStm = PlayerStm * 1.2;
                }
            }
        }
        return ZStm;
    }

    static int generateDamage(int PlayerDmg , Behavior pattern , ZOmbieClasses cls , int RegOrBoss){
        int ZDmg;
        if (RegOrBoss == 0){
            if (cls == ZOmbieClasses::Juggernaut){            
                if (pattern == Behavior::Defensive){
                    ZDmg = PlayerDmg * 1.05;
                }
                if (pattern == Behavior::Aggressive){
                    ZDmg = PlayerDmg * 1.2;
                }
            }
            if (cls == ZOmbieClasses::Knight){            
                if (pattern == Behavior::Defensive){
                    ZDmg = PlayerDmg;
                }
                if (pattern == Behavior::Aggressive){
                    ZDmg = PlayerDmg * 1.1;
                }
            }
            if (cls == ZOmbieClasses::Intelligent){            
                if (pattern == Behavior::Defensive){
                    ZDmg = PlayerDmg * 0.9;
                }
                if (pattern == Behavior::Aggressive){
                    ZDmg = PlayerDmg;
                }
            }
            if (cls == ZOmbieClasses::Theif){            
                if (pattern == Behavior::Defensive){
                    ZDmg = PlayerDmg * 0.85;
                }
                if (pattern == Behavior::Aggressive){
                    ZDmg = PlayerDmg * 0.9;
                }
            }
        }

        else{ // generating for zombie boss
            if (cls == ZOmbieClasses::Juggernaut){            
                if (pattern == Behavior::Defensive){
                    ZDmg = PlayerDmg * 1.25;
                }
                if (pattern == Behavior::Aggressive){
                    ZDmg = PlayerDmg * 1.2;
                }
            }
            if (cls == ZOmbieClasses::Knight){            
                if (pattern == Behavior::Defensive){
                    ZDmg = PlayerDmg * 1.2;
                }
                if (pattern == Behavior::Aggressive){
                    ZDmg = PlayerDmg * 1.15;
                }
            }
            if (cls == ZOmbieClasses::Intelligent){            
                if (pattern == Behavior::Defensive){
                    ZDmg = PlayerDmg * 1.15;
                }
                if (pattern == Behavior::Aggressive){
                    ZDmg = PlayerDmg * 1.10;
                }
            }
            if (cls == ZOmbieClasses::Theif){            
                if (pattern == Behavior::Defensive){
                    ZDmg = PlayerDmg * 1.10;
                }
                if (pattern == Behavior::Aggressive){
                    ZDmg = PlayerDmg * 1.10;
                }
            }
        }
        return ZDmg;
    }
    static int generateStealth(int PlayerStl , Behavior pattern , ZOmbieClasses cls , int RegOrBoss){
        
        // The numbers are just for examples . TBD

        int Zstl;
        if (RegOrBoss == 0){
            if (cls == ZOmbieClasses::Juggernaut){            
                if (pattern == Behavior::Defensive){
                    Zstl = PlayerStl * 1.05;
                }
                if (pattern == Behavior::Aggressive){
                    Zstl = PlayerStl * 1.2;
                }
            }
            if (cls == ZOmbieClasses::Knight){            
                if (pattern == Behavior::Defensive){
                    Zstl = PlayerStl;
                }
                if (pattern == Behavior::Aggressive){
                    Zstl = PlayerStl * 1.1;
                }
            }
            if (cls == ZOmbieClasses::Intelligent){            
                if (pattern == Behavior::Defensive){
                    Zstl = PlayerStl * 0.9;
                }
                if (pattern == Behavior::Aggressive){
                    Zstl = PlayerStl;
                }
            }
            if (cls == ZOmbieClasses::Theif){            
                if (pattern == Behavior::Defensive){
                    Zstl = PlayerStl * 0.85;
                }
                if (pattern == Behavior::Aggressive){
                    Zstl = PlayerStl * 0.9;
                }
            }
        }
        
        return Zstl;
    }

    //static int generateDefense(int PlayerDef , Behavior pattern , ZOmbieClasses cls){
        //int ZDefnse;
        // Same as above
        //return ZDefnse;

    //}


public:



    static Zombie createZombie(const Entity& player , int RegOrBoss){
        
        srand(time(nullptr));
        string filename = "names.txt";
        vector<string> ZombieName = randomNames(filename);

            // these are just examples:            
        Behavior pattern = generateBehavior();
        ZOmbieClasses cls = generateZombieCls();
        string name = getRandomName(ZombieName);
        int age = player.getAge() * 2;
        string gender = player.getGender();
        int hp = generateHP(player.getHP() , pattern , cls , RegOrBoss);
        int stamina = generateStamina(player.getStamina() , pattern , cls , RegOrBoss);
        int level = player.getLevel();
        int damage = generateDamage(10 , pattern , cls , RegOrBoss);
        int defense = 0.7;
        int stealth = generateStealth(0.4 , pattern , cls , RegOrBoss);
        int armor = 0.1;
        
        return Zombie(name , age , gender , hp , stamina , level , pattern  , damage , defense , stealth ,  armor , cls);
                

        
    }

    static ZombieBoss createBossZombie(const Entity& player , int RegOrBoss){

        srand(time(nullptr));
        string filename = "names.txt";
        vector<string> ZombieName = randomNames(filename);

        Behavior pattern = generateBehavior();
            ZOmbieClasses cls = generateZombieCls();
            BossSkills skill = generateBossSkill(cls);
            string name = getRandomName(ZombieName);
            int age = player.getAge() * 2;
            string gender = player.getGender();
            int hp = generateHP(player.getHP() , pattern , cls , RegOrBoss);
            int stamina = generateStamina(player.getStamina() , pattern , cls , RegOrBoss);
            int level = player.getLevel();
            int damage = generateDamage(10 , pattern , cls , RegOrBoss);
            int defense = 0.7;
            int stealth = generateStealth(0.4 , pattern , cls , RegOrBoss);
            int armor = 0.1;

            return ZombieBoss(name , age , gender , hp , stamina , level , pattern  , damage , defense , stealth ,  armor , cls , skill);
    }
    
};


void setConsoleColor(int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout.flush();
    SetConsoleTextAttribute(hConsole, color);
}

class Singleton {
public:
    static Singleton& get() {
        if (nullptr == instance)
            instance = new Singleton;
        return *instance;
    }

    // Existing interface methods go here
    int getValue() { return value; }
    void setValue(int value_) { value = value_; }

    // Destructor to clean up
    static void destruct() {
        delete instance;
        instance = nullptr;
    }

private:
    Singleton() = default; // No public constructor
    ~Singleton() = default; // No public destructor

    static Singleton* instance; // Declaration of the class variable
    int value;
};
Singleton* Singleton::instance = nullptr; // Definition of the class variable


class StoryHandler {
private:
    int chapter;
public:
    StoryHandler() : chapter(1) {}

    void displayStory() {
        string line;
        ifstream storyFile("chapter" + to_string(chapter) + ".txt");

        if (storyFile.is_open()) {
            while (getline(storyFile, line)) {
                cout << line << endl;
            }
            storyFile.close();
        } else {
            cout << "Unable to open file";
        }
    }
    void nextChapter() {
        chapter++;
    }
};

class Game {
public:
    Game() {
        int y;
        string Name;
        int choice;
        fstream store("store.txt" , ios::in | ios::out | ios::app);
        
        cout << "1.existed" << "\n2.customize\n" << "(press \"1\" for choosing amoung existed characters and for customizing press \"2\")";
        cin >> y;
        characters ch;
        if (y==1)
        {
            human* selectedCharacter = ch.choice();
            if (selectedCharacter) {
                StoryHandler story;
                while (true)
                {
                    story.displayStory();
                    srand(time(NULL));
                    while(true) {
                        int state = rand()%2;
                        if(state==0)
                        {

                        }

                    }
                }
            
            }
        
        } else if (y==2){
            string gender;
            cout << "choose a name for your character:\n";
            getline(cin ,Name);
            cout << "\n1.Male\n2.Female\n";
            cin >> gender;
            cout << "how strong you like to be?!\n" << "1.noob\n2.normal\n3.pro\n";
            cin >> choice;
            if (choice==1)
            {
                human player(Name,10 ,gender ,1 ,20 ,10 ,20);

            } else if (choice==2)
            {
            /* code */
            } else
            {
            /* code */
            }
         

        } else {
            cout << "unvalid choice\n";
        }

        }

};
class GameModel {
public:
    // Game data like player stats, game map, NPCs, etc.
    // Methods to update the game state based on actions
};

// View.h
class GameView {
public:
    // Methods to display the game state to the player
    void displayGameState(const GameModel& model);
};

// Controller.h
class GameController {
public:
    // Methods to handle user input and update the model
    void handleInput(GameModel& model);
};


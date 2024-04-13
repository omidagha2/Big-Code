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
#include <fstream>
#include <cstdlib>
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

//************************************************************************

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

enum class BossSkills{
    FireRocks,
    SummonHorse,
    SelfHealing,
    Vanishing
};

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

//***********************************************************************

class Item{
protected:
    Human* owner;
    string name;
    vector<string> description;
    int token_uses;

public:
    virtual void putInInv(Human* human);
    virtual void removeFromInv(Human* human);

    int getTokenUse(){return token_uses;}
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

public:
    virtual void attack(Entity*);
    virtual int estimateDamage(Entity* entity);

    virtual vector<DamageComponent> getDcVector();
    Weapon(string argName, vector<DamageComponent> dcs, vector<string> desc = {}, Human* argOwner = nullptr);

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
    FireArm(string argName, vector<DamageComponent> dcs, vector<string> desc, int ARGmax_ammo, int ARG_ammo, Human* argOwner=nullptr);
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
    int getTotalHealAmount();
    //switch out the inheritance just for types and the other thing


    void addVC(ValuedComponent* vc);
    void apply(Entity* entity);
    int getBenefit();
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
    int luck;
    vector<string> prompts;
public:
    virtual bool isAlive();
    void heal(int amount);
    int healAmount(int amount);
    virtual int hpFullPercent();
    virtual int calculateDmg(DamageComponent, double=1);
    void takeDamage(int damage);
    virtual void dealDamage(int amount, Entity* entity);
    virtual void consumeComponent(ValuedComponent *vc);
    virtual int calculateDmgWpn(Weapon* weapon, double mult=1);
    virtual void getAttacked(Weapon* weapon, double multiplier = 1);
    virtual void die();
    virtual void addweakness(string str){weaknesses.append(str);}
    virtual void addwithstand(string str){withstands.append(str);}

    //**************************
    virtual void Attack(Entity* target) = 0;
    void updateHP(int damage);
    //******************************

    string getRandomPrompt() {
        if (prompts.empty()) return "This one's got nothing to say";
        return prompts[rand() % prompts.size()];
    }

    Entity();
    Entity(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, string withstandstr = "", string weaknessstr = "", vector<string> argPrompts = {})
        : name(argName), age(argAge), gender(argGender), lvl(argLVL), hp(argHP), max_hp(argHP), dmg(argDMG), prompts(argPrompts) {}
    virtual string getType();
    int getHp();
    string getname();
    int getSta();
    int getHpMax();
    int getStaMax();
    int getLVL();
    int getDMG();
    void setDMG(int newDmg);
    void takeIntDamage(int);
    void setluck(int l){luck = l;}
    int getluck(){return luck;}
};


class Human: public Entity {
protected:
    Weapon* melee_weapon;
    Weapon* firearm_weapon;
    vector<Item*> inventory;
    int max_combat_tokens;
    int combat_tokens;
public:
    virtual void attackWith(Weapon* weapon, Entity* entity);
    virtual void useConsumable(Consumable*);
    virtual void takeInInv(Item* item);
    virtual void consumeConsumable(Item* consumable);
    virtual void removeFromInv(Item* item);
    virtual void addCombatTokens(int amount){
        combat_tokens = min(amount + combat_tokens, max_combat_tokens);
    }
    int effectiveValue(ValuedComponent* vcptr);
    vector<string> getItemNames();
    Human(){};



    Human(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, vector<Item*> argInv={}, vector<string> argPrompts={}, string withstandstr="", string weaknessstr="");
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
    
    Player(){};
    int atkBarGun(int offset, int length = 11, bool rawscore = false, bool showting = true, char crosshair = '^');
    int atkBarMelee(int offset);
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

    Player(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, vector<Item*> argInv={}, string withstr="", string weakstr="");
    virtual string getType();
};


class Enemy : public Entity {

//******************************************************************************
protected:
    Behavior Pattern;
    int Stealth;
public:
//***************************************************
    Enemy(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, string withstr, string weakstr, vector<string> argPrompts = {} , int stealth , Behavior pattern)
    :Entity(argName, argAge, argGender, argLVL, argHP, argDMG, withstr, weakstr, argPrompts) , Stealth(stealth) , Pattern(pattern) {}
    Enemy(){};

    int getStealth() const {
        return Stealth;
    }
    Behavior getBehavior() const {
        return Pattern;
    }
//*******************************************************************************
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
protected:
    //*************************
    ZOmbieClasses Cls;
    //*************************
public:
//********************************************************************
    Zombie(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, string withstr, string weakstr, vector<string> argPrompts = {} , int stealth , Behavior pattern , ZOmbieClasses cls)
    :Enemy(argName, argAge, argGender, argLVL, argHP, argDMG, withstr, weakstr, argPrompts , stealth , pattern ) , Cls(cls) {}
    
    void Attack(Entity* target) override {}
    ZOmbieClasses getZombieCls() const {
        return Cls;
    }
    void updatehhp(int tkDmg){
        hp -= tkDmg;
    }
    int calcZdmg();
    int calcZTakenDmg(int tkDmg);
//********************************************************************************    
    void zombieAttack(Player* player);


};

class ZombieBoss : public Enemy{

private:
    BossSkills Skill;
    int UseOfSkill = 0;
    ZOmbieClasses Cls;
public:

    ZombieBoss(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, string withstr, string weakstr, vector<string> argPrompts = {} , int stealth , Behavior pattern , ZOmbieClasses cls , BossSkills skill , int useOfSkill)
    :Enemy(argName, argAge, argGender, argLVL, argHP, argDMG, withstr, weakstr, argPrompts , stealth , pattern ) , Cls(cls) , Skill(skill) , UseOfSkill(useOfSkill) {}

    ZOmbieClasses getZombieCls() const {
        return Cls;
    }
    BossSkills getBossSkill() const{
        return Skill;
    }
    int calcBossDmg(int damg);
    int calcBossTakenDmg(int tkDmg);
    void Attack(Entity* target);
    void HealBoss(){
        int temp = hp;
        hp = temp * 1.25;
    }
    int damageOfShadow(){
        return getDMG() * 1.1;
    }
    int getUseOFSkill() const{
        return UseOfSkill;
    } 
    void setUseOfSkill(int a){
        if (a == 1){
            UseOfSkill += 1;
        }
        else{
            UseOfSkill = 0;
        }
    }
};

int ZombieBoss::calcBossDmg(int damg){    
    return damg;
}

int ZombieBoss::calcBossTakenDmg(int tkDmg){

    if (getBossSkill() == BossSkills::Vanishing){

                if (getUseOFSkill() < 3){
                    setUseOfSkill(1);
                }
                else{
                    tkDmg = 0;
                    cout << "Wow Wow , where did the Zombie go? Looks like it disapeared. Missed Shot =((" << endl;    
                }
            }
    updateHP(tkDmg);
    return tkDmg; 
}
int Zombie::calcZdmg(){
    return getDMG();
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
    updateHP(tkDmg);
    return tkDmg;
}

void ZombieBoss::Attack(Entity* target){
    
    if (getBossSkill() == BossSkills::FireRocks){

        if (getUseOFSkill() < 4){
            setUseOfSkill(1);
            calcBossDmg(getDMG());
        }
        else{
            cout << "Ah oh, Looks like a fire rock is coming to you!!" << endl;
            setUseOfSkill(0);
            calcBossDmg(30);
        }
        }
    if (getBossSkill() == BossSkills::SummonHorse){

        if (getUseOFSkill() < 4){
            setUseOfSkill(1);
            calcBossDmg(getDMG());
        }
        else{
            cout << "Oh No!! The Zombie has unleashed its horse and its coming to you!!" << endl;
            setUseOfSkill(0);
            calcBossDmg(30);
        }
    }
    if (getBossSkill() == BossSkills::SelfHealing){

        if (getUseOFSkill() < 4){
            setUseOfSkill(1);
            calcBossDmg(getDMG());
        }
        else{
            HealBoss();
            cout << "Wait, What! Did the Zombie just Heal itself? Yep, seems like it's an Intelligent one =))" << endl;
            setUseOfSkill(0);
            calcBossDmg(getDMG());
            
        }
    }
    if (getBossSkill() == BossSkills::Vanishing){

        if (getUseOFSkill() < 3){
            calcBossDmg(getDMG());
        }
        else{
            cout << "Oh , the Zombie came out of nowhere!!" << endl;
            setUseOfSkill(0);
            calcBossDmg(getDMG() * 1.1);
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

        int Zstl = 0;
        if (RegOrBoss == 0){
            if (cls == ZOmbieClasses::Juggernaut){            
                Zstl = 0;
            }
            if (cls == ZOmbieClasses::Knight){            
                Zstl = 0;
            }
            if (cls == ZOmbieClasses::Intelligent){            
                if (pattern == Behavior::Defensive){
                    Zstl = PlayerStl * 0.2;
                }
                if (pattern == Behavior::Aggressive){
                    Zstl = PlayerStl * 0.1;
                }
            }
            if (cls == ZOmbieClasses::Theif){            
                if (pattern == Behavior::Defensive){
                    Zstl = PlayerStl * 0.3;
                }
                if (pattern == Behavior::Aggressive){
                    Zstl = PlayerStl * 0.2;
                }
            }
        }
        
        return Zstl;
    }

public:
    
    static Zombie createZombie(Entity& player , int RegOrBoss){
        srand(time(nullptr));
        string filename = "names.txt";
        vector<string> ZombieName = randomNames(filename);

        Behavior pattern = generateBehavior();
        ZOmbieClasses cls = generateZombieCls();
        string name = getRandomName(ZombieName);
        int age = rand() % 150;
        string gender = "male";
        int hp = generateHP(player.getHp() , pattern , cls , RegOrBoss);
        int stamina = generateStamina(0 , pattern , cls , RegOrBoss);
        int level = player.getLVL();
        int damage = generateDamage(player.getDMG() , pattern , cls , RegOrBoss);
        int stealth = generateStealth(10 , pattern , cls , RegOrBoss);
        string withstr="";
        string weakstr="";
        vector<string> argPrompts = {};
        
        return Zombie(name , age , gender , level , hp , damage , withstr , weakstr , argPrompts ,stealth , pattern , cls);
    }
    
    static ZombieBoss createBossZombie(Entity& player , int RegOrBoss){

        srand(time(nullptr));
        int randNum = rand() % 4;
        string filename = "names.txt";
        vector<string> ZombieName = randomNames(filename);

        Behavior pattern = generateBehavior();
        ZOmbieClasses cls = generateZombieCls();
        BossSkills skill = generateBossSkill(cls);
        string name = getRandomName(ZombieName);
        int age = rand() % 150;
        string gender = "male";
        int hp = generateHP(player.getHp() , pattern , cls , RegOrBoss);
        int stamina = generateStamina(0 , pattern , cls , RegOrBoss);
        int level = player.getLVL();
        int damage = generateDamage(player.getDMG() , pattern , cls , RegOrBoss);
        int stealth = generateStealth(10 , pattern , cls , RegOrBoss);
        int useOfSkill = randNum;
        string withstr="";
        string weakstr="";
        vector<string> argPrompts = {};

        return ZombieBoss(name , age , gender , level , hp , damage , withstr , weakstr , argPrompts ,stealth , pattern , cls , skill , useOfSkill);
    }

};

//*************************************************************************************************************************************************
//**********************************************************************
//**************************************
//a punch melee weapon

class HumanEnemy : public Human, public Enemy {
    friend class Combat;
    enum State{
        CalcBestWeapon,
        Entry,
        DangerouslyLowHp,
        KindaLowHp,
        HpFine,
        AreThereTokens,
        Attack
    };
    vector<string> state_prompts;
    State current_state;
    string dialogue;
    Player* target; 
    Weapon* bw;
    int tokens_after_best_weapon;
    Consumable* bestConsumable;
public:
    void setCurrentState(State state){current_state = state;}
    State getCurrentState(){return current_state;}
    
    vector<string> getStatePrompts(){return state_prompts;}
    void setStatePrompts(vector<string> spv){state_prompts = spv;}
    int usePercentVC(ValuedComponent* vcptr);
    int usePercentConsumable(Consumable* cons);
    Weapon* findBestWeapon(Entity* target);
    HumanEnemy(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, vector<Item*> argInv={}, vector<string> randomprompts={}, vector<string> stateprs={}, string withstr="", string weakstr="");
    virtual string getType() override;
    int gettabw(){return tokens_after_best_weapon;}
    void settabw(int amount){tokens_after_best_weapon = amount;}
    Consumable* findBestConsumableForUtilization();
    Weapon* calculateBestWeapon(Player* target);
    int hpFullPercent();
};

Consumable* HumanEnemy::findBestConsumableForUtilization(){
    Consumable* bestConsumable = nullptr;
    double bestBenefitRatio = 0;

    for (Item* item : inventory) {
        Consumable* consumable = dynamic_cast<Consumable*>(item);
        if (consumable) {
            int totalBenefit = consumable->getBenefit();
            int cost = consumable->getTokenUse();
            double benefitRatio = cost > 0 ? double(totalBenefit) / cost : 0;

            if (cost <= combat_tokens - tokens_after_best_weapon && benefitRatio > bestBenefitRatio) {
                bestBenefitRatio = benefitRatio;
                bestConsumable = consumable;
            }
        }
    }
}

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

int HumanEnemy::hpFullPercent(){

};

Consumable::Consumable(string name, vector<ValuedComponent*> VCs, vector<DamageComponent> DCs, vector<string> desc, Human* owner, int tokenUses)
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

Weapon* HumanEnemy::calculateBestWeapon(Player* target){
    bw = nullptr; 
    double bestRatio = 0; 

    for (Item* item : inventory){
        Weapon* weapon = dynamic_cast<Weapon*>(item);
        if (weapon){
            int damage = weapon->estimateDamage(target);
            int cost = weapon->getTokenUse();
            double ratio = (cost > 0 ? (double(damage))/cost : 0);

            if (ratio > bestRatio){
                bestRatio = ratio;
                bw = weapon;
                tokens_after_best_weapon = combat_tokens - cost;
            }
        }
    }


    if (bw){
        nextPrompts.push_back("selected best weapon: " + bw->getname() + " with damage-to-token ratio: " + std::to_string(bestRatio));
    }
    else{
        nextPrompts.push_back("No suitable weapon found.");
    }
};

Weapon* HumanEnemy::findBestWeapon(Entity* target){
    Weapon* bestWeapon = nullptr;
    double bestRatio = 0.0;
    for (Item* item: inventory){
        Weapon* weapon = dynamic_cast<Weapon*>(item);
        if (weapon){
            int damage = weapon->estimateDamage(target);
            int tokenCost = weapon->getTokenUse();
            double ratio = tokenCost > 0 ? static_cast<double>(damage) / tokenCost : 0;
            if (ratio > bestRatio){
                bestRatio = ratio;
                bestWeapon = weapon;
            }
        }
    }
    return bestWeapon; 
}

vector<Item*> Player::getSpecialItems(){
    return special_items_inventory;
}

int Consumable::getTotalHealAmount(){
    int totalHeal = 0;
    for (auto vc: valueComponents) {
        if (auto hc = dynamic_cast<Stat::HealthComponent*>(vc)){
            totalHeal+= hc->getMaxVal();
        }
    }
    return totalHeal;
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

FireArm::FireArm(string argName, vector<DamageComponent> dcs, vector<string> desc, int ARGmax_ammo, int ARG_ammo, Human* argOwner)
:Weapon(argName, dcs, desc, argOwner){max_ammo = ARGmax_ammo; ammo = ARG_ammo == -1 ? ARGmax_ammo : ARG_ammo;};

vector<string> Item::getDesc(){
    return description;
}

void Item::setDesc(vector<string> desc){
    description = desc;
}

int Consumable::getBenefit(){
    int sum = 0;
    for (auto vc: valueComponents){
        sum += vc->getMaxVal();
    }
    for (auto dc: damageComponents){
        sum += dc.getDmg();
    }
    return sum;
};

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


void Zombie::zombieAttack(Player* player){
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

Weapon::Weapon(string argName, vector<DamageComponent> argMod, vector<string> desc, Human* argOwner)
    :Item(argName), dcvector(argMod){owner = argOwner; description = desc;};

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

Entity::Entity() : name(""), age(0), gender(""), lvl(1), hp(100), max_hp(100), dmg(10) {}

string Entity::getType() {
    return "Entity";
}

bool Entity::isAlive() {
    return hp > 0;
}

int Entity::getHp() {
    return hp;
}


int Entity::getHpMax() {
    return max_hp;
}

int Entity::getLVL() {
    return lvl;
}

int Entity::getDMG() {
    return dmg;
}

void Entity::setDMG(int newDmg) {
    dmg = newDmg;
}

int Entity::healAmount(int amount){
    return min(hp + amount, max_hp) - hp;
}

void Entity::heal(int amount) {
    hp = min(max_hp, hp + amount);
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

void Entity::consumeComponent(ValuedComponent* vc) {
    string type = vc->getType();
    if (type == "HealthComponent"){
        this->heal(vc->getMaxVal());
    }
    else if (type == "StaminaComponent"){
        if (auto a = dynamic_cast<Human*>(this)){
            a->addCombatTokens(vc->getMaxVal());
        }
    }
}

Human::Human(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, vector<Item*> argInv, vector<string> argPrompts, string withstandstr, string weaknessstr)
    :Entity(argName, argAge, argGender, argLVL, argHP, argDMG, withstandstr, weaknessstr, argPrompts), inventory(argInv){}

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



Player::Player(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, vector<Item*> argInv, string withstr, string weakstr)
:Human(argName, argAge, argGender, argLVL, argHP, argDMG, argInv, {}, withstr, weakstr){inventory = argInv;}

string Player::getType() {
    return "Player";
}

string Enemy::getType() {
    return "Enemy";
}



HumanEnemy::HumanEnemy(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, vector<Item*> argInv, vector<string> randomprompts, vector<string> stateprs, string withstr, string weakstr)
:Human(argName, argAge, argGender, argLVL, argHP, argDMG, argInv, randomprompts, withstr, weakstr){state_prompts = stateprs;}

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
        return min(vcptr->getMaxVal() + combat_tokens, max_combat_tokens);
    }
}

int DamageComponent::simulateDamage(Entity* entity) {
    return entity->calculateDmg(*this);
}
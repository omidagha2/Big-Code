#include <string>
#include <vector>
using namespace std;

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

class item{
protected:
    string name;
    int use_limit;
    int uses_left;
    int size;

public:
    item(string argName, int argU_Limit, int argU_Left, int argSize);
    string getname();
    void setName(string argName);
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

class recovery_item: public consumable{

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

public:
    virtual void attack(entity*)=0;

    entity();
    entity(string argName, int argAge, string argGender, int argLVL=1, int argHP=0, int argDMG=0, int argSTA=0)
    :name(argName), age(argAge), gender(argGender), lvl(argLVL), hp(argHP), dmg(argDMG), sta(argSTA){};

};

class human: public entity{
protected:
    item item_at_hand;
    vector<item> inventory;
    int skills[SKILLS_IMPLEMENTED];

public: 
    virtual void attack(entity*);
    void changeHeldItem();
};

class enemy: public entity{
protected:
    STATE current_state;
    vector<STATE> available_states;
public:
    void attack(human*);
};

class HumanEnemy: public human{

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



class Game{
    STAGE stage;
};

#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
using namespace std;

enum STATE{

};

enum class ZOmbieClasses{
    Juggernaut,
    Knight,
    Intelligent,
    Thief
    //maybe some more classes
};

enum class Behavior{
    Aggressive,
    Defensive,
    // some more behaviors TBD
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
        case(ZOmbieClasses::Thief):
            return "Thief";
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
    void updateDmg(){
        int temp = getStamina();

    } 
    void updatehhp(int tkDmg){
        hp -= tkDmg;
    }
};


class HumanEnemy : public Player{

    // some code to initialize and etc.


};
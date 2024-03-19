#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

enum STATE{

};

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
    
    string Cls;
    vector<string> clss;
    int Damage , Defense , Stealth , Armor;

    STATE current_state;
    vector<STATE> available_states;

public:

    Enemy() = default;
    Enemy(string& name , int age , string gender , int hp , int stamina , int level , string& cls, int damage , int defense , int stealth , int armor) : 
    Entity(name , age , gender , hp , stamina , level) , Cls(cls) ,Damage(damage) , Defense(defense) , Stealth(stealth) , Armor(armor) {}

    void Attack(Entity& target) override {

        // some code and story tellings
    }

    string getCls() const {
        return Cls;
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

};


class Zombie : public Enemy{

public:
    
    Zombie() = default;
    Zombie(string& name , int age , string& gender , int hp , int stamina , int level , string& cls, int damage , int defense , int stealth , int armor) : 
    Enemy(name , age , gender , hp , stamina , level , cls , damage , defense , stealth ,  armor){}

    void Attack(Entity& target) override {

        int damageTaken = getDamage();
        updateHP(damageTaken);
    }


};


class ZombieFactory : public Zombie {

public:



    static Zombie createZombie(const Entity& player){

        // these are just examples:


        vector<string> clss = {"Juggernaut" , "Knight" , "Intelligent" , "Theif"};
        int randNum = rand() % 4;


        string name = "";
        int age = player.getAge() * 21;
        string gender = player.getGender();
        int hp = player.getHP() * 1.2;
        int stamina = player.getStamina() * 0.9;
        int level = player.getLevel();
        string cls = clss[randNum];
        int damage = 2;
        int defense = 0.7;
        int stealth = 0.3;
        int armor = 0;

        return Zombie(name , age , gender , hp , stamina , level , cls , damage , defense , stealth ,  armor);

        

    }
    

};

class HumanEnemy : public Player{

    // some code to initialize and etc.


};

class Juggernaut : public Zombie {};
class Knight : public Zombie {}; 
class Intelligent : public Zombie {};
class Theif : public Zombie {};

int main(){

    string name , gender;
    int hp , lvl , stamina , age;
    cin >> name  >> age >> gender >> hp >> stamina >> lvl;
    Player pl1(name , age , gender , hp , stamina , lvl);

    Zombie z1 = ZombieFactory::createZombie(pl1);
    Zombie z2 = ZombieFactory::createZombie(pl1);

    cout << z1.getDamage() << endl;
    cout << z2.getGender() << endl;
    return 0;
}
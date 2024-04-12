#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "uml.hpp"
using namespace std;

int useOfSkill = 0;

enum class BossSkills{
    FireRocks,
    SummonHorse,
    SelfHealing,
    Vanishing
};

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

class ZombieBoss : public Zombie{

private:

    BossSkills Skill;
public:
    
    ZombieBoss(string& name , int age , string& gender , int hp , int stamina , int level , Behavior pattern, int damage , int defense , int stealth , int armor , ZOmbieClasses cls , BossSkills skill) :
        Zombie(name , age , gender , hp , stamina , level , pattern , damage , defense , stealth ,  armor , cls) , Skill(skill) {}

    BossSkills getBossSkill() const{
        return Skill;
    }

    void Attack(Entity& target) override {
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

    void HealBoss(){
        hp = hp * 1.25;
    }
    int damageOfShadow(){
        return Damage * 1.1;
    } 

};

//void ZombieBoss::Attack(Entity& target){
//
//    if (getBossSkill() == BossSkills::FireRocks){
//
//        if (useOfSkill < 4){
//            //return getDamage();
//            useOfSkill += 1;
//        }
//        else{
//            cout << "Ah oh, Looks like a fire rock is coming to you!!" << endl;
//            // return severe Damage
//            useOfSkill = 0;
//        }
//    }
//    if (getBossSkill() == BossSkills::SummonHorse){
//
//        if (useOfSkill < 4){
//            //return getDamage();
//            useOfSkill += 1;
//        }
//        else{
//            cout << "Oh No!! The Zombie has unleashed its horse and its coming to you!!" << endl;
//            // return severe Damage
//            useOfSkill = 0;
//        }
//    }
//    if (getBossSkill() == BossSkills::SelfHealing){
//
//        if (useOfSkill < 4){
//            useOfSkill += 1;
//        }
//        else{
//            HealBoss();
//            cout << "Wait, What! Did the Zombie just Heal itself? Yep, seems like it's an Intelligent one =))" << endl;
//            useOfSkill = 0;
//            int dm = damageOfShadow();
//            //return getDamage();
//        }
//    }
//    if (getBossSkill() == BossSkills::Vanishing){
//
//        if (useOfSkill < 3){
//            //return getDamage();
//            useOfSkill += 1;
//        }
//        else{
//            cout << "Wow Wow , where did the Zombie go? Looks like it disapeared. Missed Shot =((" << endl;
//            useOfSkill = 0;
//        }
//    }
//
//}
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

int main(){

    // james 20 male 75 20 6
    string name , gender;
    int hp , lvl , stamina , age;
    cin >> name  >> age >> gender >> hp >> stamina >> lvl;
    Player pl1(name , age , gender , hp , stamina , lvl);

    Zombie z1 = ZombieFactory::createZombie(pl1 , 0);
    ZombieBoss z2 = ZombieFactory::createBossZombie(pl1 , 1);

    cout << "dmg : " <<z1.getDamage() << endl;
    cout << "name: " << z2.getName() << endl;
    cout  << static_cast<int>(z2.getBehavior()) << endl;
    cout << "Behavior: " << BehaviorToString(z2.getBehavior()) << endl;
    cout << "Class: " << ZombieClassToString(z1.getZombieCls()) << endl;
    cout << "skill : " << BossSkillsTostring(z2.getBossSkill());
    
    return 0;
}
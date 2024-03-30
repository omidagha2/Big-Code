#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "uml.hpp"
using namespace std;


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

class ZombieFactory : public Zombie {


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


    static int generateHP(int PlayerHP , Behavior pattern , ZOmbieClasses cls){
        
        int ZHP;

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

        return ZHP;    
    }

    static int generateStamina(int PlayerStm , Behavior pattern , ZOmbieClasses cls){
        int ZStm;

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

        return ZStm;
    }

    static int generateDamage(int PlayerDmg , Behavior pattern , ZOmbieClasses cls){
        int ZDmg;

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

        return ZDmg;
    }
    static int generateStealth(int PlayerStl , Behavior pattern , ZOmbieClasses cls){
        
        // The numbers are just for examples . TBD

        int Zstl;

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
        return Zstl;
    }

    //static int generateDefense(int PlayerDef , Behavior pattern , ZOmbieClasses cls){
        //int ZDefnse;
        // Same as above
        //return ZDefnse;

    //}


public:



    static Zombie createZombie(const Entity& player){
        srand(time(nullptr));

        // these are just examples:


        
        int randNum = rand() % 4;

        Behavior pattern = generateBehavior();
        ZOmbieClasses cls = generateZombieCls();
        string name = "";
        int age = player.getAge() * 2;
        string gender = player.getGender();
        int hp = generateHP(player.getHP() , pattern , cls);
        int stamina = generateStamina(player.getStamina() , pattern , cls);
        int level = player.getLevel();
        int damage = generateDamage(10 , pattern , cls);
        int defense = 0.7;
        int stealth = generateStealth(0.4 , pattern , cls);
        int armor = 0.1;
        

        return Zombie(name , age , gender , hp , stamina , level , pattern  , damage , defense , stealth ,  armor , cls);

        

    }
    

};

int main(){

    string name , gender;
    int hp , lvl , stamina , age;
    cin >> name  >> age >> gender >> hp >> stamina >> lvl;
    Player pl1(name , age , gender , hp , stamina , lvl);

    Zombie z1 = ZombieFactory::createZombie(pl1);
    Zombie z2 = ZombieFactory::createZombie(pl1);

    cout << "dmg : " <<z1.getDamage() << endl;
    cout << z2.getGender() << endl;
    cout  << static_cast<int>(z2.getBehavior()) << endl;
    cout << "Behavior: " << BehaviorToString(z2.getBehavior()) << endl;
    cout << "Class: " << ZombieClassToString(z1.getZombieCls()) << endl;

    
    return 0;
}
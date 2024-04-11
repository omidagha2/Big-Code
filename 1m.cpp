#include <string>
#include <vector>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

const int SKILLS_IMPLEMENTED = 2;

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
private:
   
protected:
    string name;
    int use_limit;
    int uses_left;
    int size;
    string weapons[9] = {"Kalashnikov", "pistol", "graneid", "sks", "m14" ,"knife" , "bandaids" , "adrenaline" ," exir_st"};

public:
    item(int argU_Limit, int argU_Left, int argSize){}
    string nameofIt(){ cin >> name; return name;}
    item(){}
};

class weapon: public item{
protected:
    MOD modifier;
    int dmg;
public:
    weapon(MOD argMod, int argDMG, int argSize)
    :item(infinite, infinite, argSize), modifier(argMod), dmg(argDMG) {

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
    : entity(argName, argAge, argGender, argLVL, argHP, argDMG, argSTA),item_at_hand(0,0,0) {
        
    }
    human(){}
    virtual void attack(entity* x) {

    }
    item changeHeldItem(string pack) {
        for (int i = 0; i < 3; i++)
        {
            if (inventory[i][0]==pack)
            {
                for (int j = 0; j < inventory[i].size(); j++)
                {
                    cout << inventory[i][j] << ",,";

                }
                item_at_hand.nameofIt();
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

    void attack(entity* a) {
        human* x = choice();
        if (x != nullptr) { // Check if the choice is valid
            int newhp = x->getHp() - a->getDmg();
            x->setHp(newhp);
            cout << x->getName() << " takes " << a->getDmg() << " damage.\n";
            if (x->getHp() <= 0) {
                cout << x->getName() << " has been defeated!\n";
            }
        }
    }

    bool isDefeated() const {

        return hp <= 0;
    }

};
class HumanEnemy: public human{
     bool isboss;
public:
    HumanEnemy(bool boss=false):isboss(boss) {}
};
class enemies: public HumanEnemy{
    vector<human> enemy;
public:
    enemies() {
        enemy.emplace_back("Stenchurion", 20, "Male", 1, 100, 5, 15);
        enemy.emplace_back("Cannibelle", 20, "Female", 1, 100, 7, 10);
        enemy.emplace_back("Magmalice", 20, "Male", 1, 200, 15, 10);
        enemy.emplace_back("Salamarauder", 20, "Female", 1, 150, 10, 15);
        enemy.emplace_back("Bewarewolf", 20, "Male", 1, 100, 15, 10);
        enemy.emplace_back("Lunatick", 20, "Male", 1, 120, 20, 10);
        enemy.emplace_back();
        enemy.emplace_back();
        enemy.emplace_back();
        enemy.emplace_back();

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
        cout << "1.existed" << "\n2.customize\n" << "(press \"1\" for choosing amoung existed characters and for customizing press \"2\")";
        cin >> y;
        characters ch;
        if (y=='1')
        {
            human* selectedCharacter = ch.choice();
            if (selectedCharacter) {
                StoryHandler story;
                while (true)
                {
                    story.displayStory();
                }
            
            }
        
        } else if (y=='2'){
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
#include <vector>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <ctime>

using namespace std;
class characters;

const int SKILLS_IMPLEMENTED = 2;

class item{
public:
    string name;
    double price;
    int quantity;
    item(string n, double p, int q)
        : name(n), price(p), quantity(q) {}
    item()=default;
    string getName() {return name;}
    int getQ() {return quantity;}
    void setQ(int a) {quantity=a;}
    double getPrice() {return price;}
};

class weapon: public item{
protected:
    int dmg;
public:
    weapon()=default;
    weapon(string name, int argDMG, double price)
    :item(name,argDMG,price), dmg(argDMG) {
    }
    int getDamage() {return dmg;}
};

class store:public weapon{
protected:
    vector<weapon> weapons;
    vector<item> items;

public:
    store(){
        weapons.emplace_back("Kalashnikov", 10,5);
        weapons.emplace_back("pistol", 8,5);
        weapons.emplace_back("graneid", 10,10);
        weapons.emplace_back("sks", 20,10);
        weapons.emplace_back("m14", 15,10);
        weapons.emplace_back("knife", 5,5);
        items.emplace_back("bondAids",3,10);
        items.emplace_back("adrenalin",3,10);
        items.emplace_back("meet",10,10);
        items.emplace_back("cofee",5,10);
        items.emplace_back("smoke",3,10);

    }
    void displayStore (string s)
    {
        if(s=="weapon"){
        cout << endl << "weapons at store:\n";
        for (int i = 1; i <= weapons.size(); i++)
        {
            cout << i << ". " << weapons[i-1].getName() << "\ndamage: " << weapons[i-1].getDamage() << " | " << weapons[i-1].price << "$" << endl;  
        }
        } else{
        cout << "Items at store to by:\n";
        for (int i = 0; i < items.size(); i++)
        {
            cout << (i+1) << ". " << items[i].getName() << " | " << items[i].price << "$  | " << items[i].quantity << endl; 
        }
        }
        
        
    }
    item buyItem(){
        int b;
            displayStore("item");
            cin >> b;
            items[b-1].setQ(items[b-1].getQ()-1);
            
            return items[b-1];
        } 
    weapon buywep(){
        int b;
        displayStore("weapon");
        cin >> b;
        weapons[b-1].setQ(weapons[b-1].getQ()-1);
        return weapons[b-1];
    }
};

 class entity{
protected:
    string name;
    int age;
    string gender; 
    int lvl;
    int hp;
    int sta;

public:
    entity() : name(""), age(0), gender(""), lvl(1), hp(100), sta(10){}
    // virtual void attack(characters& player,humanEnemies& x,weapon& weapon)=0;
    entity(string argName, int argAge, string argGender, int argLVL=1, int argHP=0, int argSTA=0)
    :name(argName), age(argAge), gender(argGender), lvl(argLVL), hp(argHP), sta(argSTA){}
    string getName() const {return name;}
    int getLvl() const {return lvl;}
    int getSta() const {return sta;}
    void setSta(int newsta) {sta=newsta;}
    int getHp() const {return hp;}
    void setHp(int newhp)
    {
        hp=newhp;
    }
    void updateHP(int damage){

        hp -= damage;
        if (hp < 0){

            hp = 0;
        }
    }
    
};

class human: public entity{
protected:
    weapon weapon_at_hand;
    item item_at_hand;
    int coin;
    vector<weapon> inventorywep={{"knife", 5,5}};
    vector<item> inventoryit={{"bondAids",3,10}};

public: 
    human()=default;
    human(string argName, int argAge, string argGender, int argLVL=1, int argHP=0, int argSTA=0,int argCoin=0)
    : entity(argName, argAge, argGender, argLVL, argHP, argSTA),item_at_hand("",0,0) {
        
    }
    void attack(human& player,entity& x,weapon& weapon) {
        int a = x.getHp()-weapon.getDamage();
        x.setHp(a);
        player.setSta(player.getSta()-1);
        cout << "you have taken "<< a << " damage from your enemy\n";
        if (a<=0)
        {
            cout << "enemy has died\n";
            exit(0);
        }
        
    }
    weapon changeHeldwep() {
        int a;
        for (int i = 0; i < inventorywep.size(); i++)
        {
           cout << (i+1) << inventorywep[i].getName() << endl;
        }
        cout << "what weapon?\n";
        cin >> a;
        weapon_at_hand=inventorywep[a-1];
        return weapon_at_hand;
    }
    item changeHeldit() {
        int a;
        for (int i = 0; i < inventoryit.size(); i++)
        {
           cout << (i+1) << inventoryit[i].getName() << endl;
        }
        cout << "what item?\n";
        cin >> a;
        item_at_hand=inventoryit[a-1];
        return item_at_hand;

    }
    int getcoin() const {return coin;}
    void setCoin(int a) {coin=a;}
    void updateInventory(weapon& i) {
        inventorywep.push_back(i);
    }
    void updateInventorry(item& i) {
        inventoryit.push_back(i);
    }

};

class characters: public human{
    vector<human> chars;
public:
   
    characters() {
        // Directly initialize the characters in the constructor
        chars.emplace_back("Thalion", 20, "Male", 1, 50, 10,100);
        chars.emplace_back("Eirwyn", 25, "Male", 1, 50, 20,100);
        chars.emplace_back("Brondar", 20, "Male", 1, 100, 30,100);
        chars.emplace_back("Mirelle", 20, "Female", 1, 50, 35,100);
        chars.emplace_back("Kaelum", 20, "Male", 1, 40, 50,100);
        chars.emplace_back("Seraphina", 20, "Female", 1, 45, 45,100); 
        chars.emplace_back("Draxen", 20, "Male", 1, 35, 25,100);
        chars.emplace_back("Arianya", 20, "Female", 1, 100, 35,100);
        chars.emplace_back("Fenris", 20, "Male", 1, 55, 40,100);
        chars.emplace_back("Lyrielle", 20, "Female", 1, 25, 100,100);
    }
    human choice()
    {
        int a;
        cout << "\nChoose a character\n";
        displaychars();
        cin >> a;
        return chars[a-1];
    }

    
    void displaychars(){
        cout << "you can choose..\n";
        for (int i = 0; i < chars.size(); i++)
        {
            cout << (i+1) << ". " << "Name: " << chars[i].getName() << endl << "Level: " << chars[i].getLvl() << endl;
            cout << "Stamina: " << chars[i].getSta() << endl << "Coin: " << chars[i].getcoin() << endl;
        }
        
    }

    void attack(human& player,entity& x,weapon& weapon){
        int a = x.getHp()-weapon.getDamage();
        x.setHp(a);
        player.setSta(player.getSta()-1);
        cout << "you have taken "<< a << " damage from your enemy\n";
        if (a<=0)
        {
            cout << "enemy has died\n";
            exit(0);
        }


    }

    bool isDefeated() const {

        return hp <= 0;
    }

};


class humanEnemies :public entity {
    vector<entity> enemy;
public:
    humanEnemies() {
        enemy.emplace_back("Stenchurion", 20, "Male", 1, 100, 15);
        enemy.emplace_back("Cannibelle", 20, "Female", 1, 100, 10);
        enemy.emplace_back("Magmalice", 20, "Male", 1, 200, 10);
        enemy.emplace_back("Salamarauder", 20, "Female", 1, 150, 15);
        enemy.emplace_back("Bewarewolf", 20, "Male", 1, 100, 10);
        enemy.emplace_back("Lunatick", 20, "Male", 1, 120, 10);
    }
    entity choose(int a) {
        return enemy[a];
    }
    void attack(human& player,entity& x,weapon& weapon) {
        int a=player.getHp()-weapon.getDamage();
        player.setHp(a);
        x.setSta(x.getSta()-2);
        cout << "enemy has taken " << a << " damage from you\n";
        if (a<=0)
        {
            cout << "you have died\n";
            exit(0);
        }

    }

    bool isDefeated() const {

        return hp <= 0;
    }
    weapon change(int a) {
        weapon wep[3]={{"Kalashnikov", 10,5},{"pistol", 8,5},{"graneid", 10,10}};
        return wep[a];
    }

};
//////////////////

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
                setConsoleColor(5);
                cout << line << endl;
                setConsoleColor(15);
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
string prompts[5]={"the wolf is here what would you do?\n","a zombie is here what would yo do?\n","a knight is here what would you do?\n","an strong enemy is here what would you do?\n ","the bear is here what would you do?\n"};
class Game {
public:
    Game() {
        int y;
        string Name;
        int choice;
        // fstream store("store.txt" , ios::in | ios::out | ios::app);
        cout << "1.existed" << "\n2.customize\n" << "(press \"1\" for choosing amoung existed characters and for customizing press \"2\")";
        cin >> y;
        characters ch;
        srand(time(0));
        
        if (y==1)
        {
            human selectedCharacter = ch.choice();
            while(true){
            int a=rand()%2;
            if(a==0) {
                store st;
                item x=st.buyItem();
                weapon y=st.buywep();
                ch.updateInventorry(x);
                ch.updateInventory(y);
                
            } else
            {
                while (true)
                {
                    int r=rand()%5;
                    humanEnemies en;
                    entity enemy=en.choose(r);
                    cout << prompts[r];
                    cout << "1.for attack  2.for healing\n";
                    
                    while (enemy.getHp()>=0 || ch.getHp()>=0)
                    {
                        int b;
                        cin >> b;
                    
                    if(b==1){
                        weapon wep=ch.changeHeldwep();
                        int e=rand()%3;
                        weapon wepenem=en.change(e);

                        ch.attack(ch,enemy,wep);
                        int d=rand()%5;
                        en.attack(ch,enemy,wepenem);
                        
                        
                    }

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


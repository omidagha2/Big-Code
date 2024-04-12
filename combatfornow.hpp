#include "objects2.hpp"



struct ItemFactory {
public:
    static vector<Item*> getAllPossibleItems() {
        vector<Item*> items;
        // Define various items
        items.push_back(new Consumable("Health Kit", {new Stat::HealthComponent(50)}, {}, {"Heals 50 HP.", "Some bandaid and some magical spray!"}));
        items.push_back(new Consumable("Round Candy", {new Stat::StaminaComponent(1)},  {"Increases stamina. ", "Super sweet, super energizing! no wonder mom hid them all for herself"}));
        items.push_back(new Consumable("Grenade", {}, {DamageComponent(3, DamageComponent::TYPE::explosion)}, {"Deals 30 damage.", "You don't remember where you found this."}));
        items.push_back(new Weapon("Laser Gun", {DamageComponent(4, DamageComponent::TYPE::fire)}));
        items.push_back(new Weapon("Baseball Bat", {DamageComponent(10)}, {}));
        // Add more items as needed
        return items;
    }
};
//the fire is liquid
//enemy gets inventory filled with 5 random consumables, a weapon, and a melee. if possible there can be a guy who holds 2 weapons.

namespace level1enemies{
    
}
namespace level2enemies{

}
namespace level3enemies{
//kazem final boss
//or maybe mahdi
}
// list of prompts for enemies.
class Combat{
    Player* you;
    Enemy* foe;
    public:
    Combat(Player* player, Enemy* target){you = player; foe = target;}
    Player* getPlayer(){return you;}
    Entity* getFoe(){return foe;}
    void pushPrompt(){
        nextPrompts.push_back(foe->getname() + " attacked you for " + to_string(foe->getDMG()) + " hp!");
    }
    int foeAttack(){
        if (auto zomb = dynamic_cast<Zombie*>(foe)){
            you->takeIntDamage(foe->getDMG());
            pushPrompt();
        }
        else if (auto man = dynamic_cast<HumanEnemy*>(foe)){//fsm here
            runfsm();
        }
    }
    int attackFoe(){
        you->setCombatTokens(you->getMaxCombatTokens());

        //prompt, eventually use item.  
        while (you->getCombatTokens() > 0){
            utils::cls();
            vector<string> nps = utils::popNextPrompts();
            vector<string> precombatprompt = {"You have @~", to_string(you->getCombatTokens()), "~@ tokens left.", "What will you do? "};
            for (string p: precombatprompt){
                nps.push_back(p);
            }
            int choice = utils::promptUser({"Attack with a gun", "Attack with a melee weapon", "Use a consumable", " you've got"}, nps);
            switch (choice){
                case 1:
                //show weapon stats and desc. first stats, then choices, then slowprint desc.
                
                int yn = utils::promptUser({"yes", "no"}, /*stats*/{},{(you->getFireArm())->getDesc(), {"You look into " + foe->getname() + "'s eyes. "}});
                if (yn == 2) break;
                int score = you->atkBarGun(0);
                cout <<"  x"<< score/6.0;
                Sleep(500);
                foe->getAttacked(you->getFireArm(), score/6.0);
                nextPrompts.push_back("You dealt " + to_string(foe->calculateDmgWpn(you->getFireArm())) + " damage to " + foe->getname());
            }
        }
    }

    void runfsm(){
        
    }
};

class MultiplayerCombat{
private:
    Player boy;
    Player girl;
    bool turnOfBoy;  // True if it's the boy's turn, false if it's the girl's

public:
    MultiplayerCombat(): turnOfBoy(false){
        utils::slowPrintPrompts({"There's a boy playing with some toys.", "He has an awesome laser gun.", "What is his name? "});
        string name;
        cin >> name;
        // boy = Player(name, );//!
    }

    void startCombat() {
        while (boy.isAlive() && girl.isAlive()) {
            displayTurnPrompt();
            // if (turnOfBoy) {
            //     boy.attack(&girl);
            // } else {
            //     girl.attack(&boy);
            // }
            turnOfBoy = !turnOfBoy;
            if (!boy.isAlive() || !girl.isAlive()) {
                announceWinner();
                break;
            }
        }
    }

    void displayTurnPrompt(){
        utils::promptUser({},{turnOfBoy ? boy.getname() : girl.getname() + "'s turn. Get ready for some action!\n"});
        utils::promptUser({},{turnOfBoy ? "The Boy readies his laser gun!" : "The Girl waves her sparkly magic wand!"});
    }

    void announceWinner(){
        if (!boy.isAlive()){
            utils::slowPrint("Girl wins with her unstoppable magic powers!");
        } 
        else if (!girl.isAlive()){
            utils::slowPrint(" wins with his awesome laser gun skills!");
        }
    }
};

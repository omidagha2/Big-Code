#include "objects2.hpp"



struct ItemFactory {
public:
    static vector<Item*> getAllPossibleItems() {
        vector<Item*> items;
        // Define various items
        items.push_back(new Consumable("Health Kit", {new Stat::HealthComponent(50)}, {"Heals 50 HP. A magical spray!"}));
        items.push_back(new Consumable("Round Candy", {new Stat::StaminaComponent(10)}, {"Increases stamina. Super sweet!", "no wonder mom hid them all for herself"}));
        items.push_back(new Consumable("Grenade", {new Stat::HealthComponent(-30)}, {"Deals 30 damage. It's a loud balloon pop!"}));
        items.push_back(new Weapon("Laser Gun", {DamageComponent(15, DamageComponent::TYPE::fire)}, 15, nullptr));
        items.push_back(new Weapon("Baseball Bat", {DamageComponent(10)}, 10, nullptr));
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
    Entity* foe;
    public:
    Combat(Player* player, Entity* target){you = player; foe = target;}
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
            man->attackWith(man->getItemAtHand(), you);
            pushPrompt();
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
};

class Combat1: public Combat{//for regular zombies and stuff, just a vector of prompts from the narrator. 
    // vector<string> prompts;
    // string default_prompt;
    // public:
    // Combat1(string dp = "", vector<string> ARGprompts = {}){
    //     prompts = ARGprompts;
    //     default_prompt = dp;
    // }
    

};

class Combat2: public Combat{//for those who talk a lot

};
#include <iostream>
#include <typeinfo>
#include "combatfornow.hpp"
using namespace std;


int main(){
//assume combat
    // HumanEnemy wrench("mark's first wrench", 12, "male");
    // Entity* equipped = &wrench;
    // cout << typeid(dynamic_cast<HumanEnemy*>(equipped)).name();

    //I'm thinking we don't really need value for valued compos rn, they're easily calculated with min

    // Human bro("Yasin", 19, "male");
    // bro.takeDamage(12);
    // Stat::HealthComponent hp(100);
    // Stat::StaminaComponent sta(100);
    // Consumable yasincake("yasin's mom made this", 1, 1, {new Stat::HealthComponent(100), &sta});
    // bro.takeInInv(&yasincake);
    // vector<string> prompts1 = {"hello!", "welcome to the apocalypse."};
    // for (Item* i: bro.getInv()) utils::slowPrintPrompts(prompts1);


    Player ali("ali", 12, "male");
    ali.menuPrompt();
    // cout << endl << ali.atkBar();

    //how combat?
    //there should be rewards, consumable & coins.
    //there should be turns
    //after each turn, update inventories, update hp, pass turn. (currently for one player vs. one enemy only) 
    //not in combat function, maybe take care of get_damaged and/or other stuff like that inside the player & other guy functions
    //item id's?
}
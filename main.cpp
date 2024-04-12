#include <iostream>
#include <typeinfo>
#include "combatfornow.hpp"
using namespace std;
using namespace utils;

int main(){
    //the narrator speaks archaic english.
    //there's a lot of things that remind you of other things. like bullet tape
    int a = time(0);
    cout << "Seed: " << a << endl;
    srand(a);
//assume combat
    // HumanEnemy wrench("mark's first wrench", 12, "male");
    // Entity* equipped = &wrench;
    // cout << typeid(dynamic_cast<HumanEnemy*>(equipped)).name();

    //I'm thinking we don't really need value for valued compos rn, they're easily calculated with min
    Player p1 = Player("kazem", 12, "male", 1, 20, 1);
    FireArm g1("kazem's glare", {DamageComponent(10, DamageComponent::TYPE::fire)}, {"Deals 10 damage. Inflicts BURN.", "Ever wondered how he looks without his glasses? "}, 999, 999);
    p1.takeInInv(&g1);

    HumanEnemy p2("erfan", 21, "male", 1, 20, 1);

    // bro.takeDamage(12);
    // Stat::HealthComponent hp(100);
    // Stat::StaminaComponent sta(100);
    // Consumable yasincake("yasin's mom made this", 1, 1, {new Stat::HealthComponent(100), &sta});
    // bro.takeInInv(&yasincake);
    // vector<string> prompts1 = {"hello!", "welcome to the apocalypse."};
    // for (Item* i: bro.getInv()) utils::slowPrintPrompts(prompts1);
    
    // for (int i = 0; i < 256; i++) cout << i << ": " << char(i) << endl;
    // ali.menuPrompt();
    // Combat combat(&bro, &zomb);
    // combat.foeAttack();
    // combat.attackFoe();
    // utils::slowPrintPrompts(nextPrompts);

    // cout << endl << ali.atkBar();
    // cout << utils::slowPrintPrompts({"the enemy attacked you for 10 damage!","you are dead!"}, {' '});
    // cout << utils::promptUser({"bruh", "sis", "ma", "daddy"}, {"brother", "thinks"}, {{"favorite"}, {"least favorite"}, {"lo@ve", "love", "lo@ve", "love"}, {"love"}} );

    //how combat?
    //there should be rewards, consumable & coins.
    //there should be turns
    //after each turn, update inventories, update hp, pass turn. (currently for one player vs. one enemy only) 
    //not in combat function, maybe take care of get_damaged and/or other stuff like that inside the player & other guy functions
    //item id's?
}
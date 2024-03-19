#include <iostream>
#include "objects.hpp"
using namespace std;


int main(){
//assume combat
    Human michael("michael", 12, "male");
    HumanEnemy boss1("bruh", 9, "female");
    
    CombatController combat(michael, boss1);
    
    //how combat?
    //there should be rewards, consumable & coins.
    //there should be turns
    //after each turn, update inventories, update hp, pass turn. (currently for one player vs. one enemy only) 
    //not in combat function, maybe take care of get_damaged and/or other stuff like that inside the player & other guy functions
    
}


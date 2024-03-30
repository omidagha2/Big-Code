#include <iostream>
#include <typeinfo>
#include "objects.hpp"
using namespace std;


int main(){
//assume combat
    HumanEnemy wrench("mark's first wrench", 12, "male");
    Entity* equipped = &wrench;
    cout << typeid(dynamic_cast<HumanEnemy*>(equipped)).name();

    //how combat?
    //there should be rewards, consumable & coins.
    //there should be turns
    //after each turn, update inventories, update hp, pass turn. (currently for one player vs. one enemy only) 
    //not in combat function, maybe take care of get_damaged and/or other stuff like that inside the player & other guy functions
    
}


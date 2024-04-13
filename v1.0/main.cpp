#include <iostream>
#include <typeinfo>
#include "multi.hpp"
using namespace std;
using namespace utils;
//different hat everytime
int main(){
    static int beatengame = 0;
    while (true){
        int balance = 0;
        if (beatengame == 0){
            singleplayer:
            Player p1 = Player("You", 12, "male", 1, 40, 1, {Items::getAllPossibleItems()[0]}, "", "");
            for (int i = 0; i < 9; i++){
            slowPrintPrompts(popNextPrompts());
                int n = roll(3) + roll(3);
                if (n == 0){
                    //zombie, normal or jugger or ghosty
                    Enemy* enemy = Enemies::getghoul(p1.getLVL(), p1.getluck());
                    Combat combat(&p1, enemy);   
                    p1.updateRelics();         
                    if (combat.gameloop()){
                        slowPrint("You lost! May you succeed in later endeavors.\n");
                        Sleep(1000);
                    }
                    else{
                        slowPrint("You won! as a reward, you get: \n+50 coins"); 
                        balance += 50;
                        p1.setlvl(p1.getLVL() + 1);
                        if(roll(20)){
                            slowPrint("you found a ~relic~ How exciting! \nHere's a list of all the relics you have: \n");
                            int i = rand()%7;
                            relics[i] = true;
                            view::showrelics;
                        }

                    }
                }
                else if (n == 1){
                    //human enemy
                    Enemy* enemy = Enemies::getnerd(p1.getLVL(), p1.getluck());
                    Combat combat(&p1, enemy);
                    p1.updateRelics(); //updated tokens too
                    if (combat.gameloop()){
                        slowPrint("You lost! May you succeed in some other endeavor.\n");
                        Sleep(1000);
                    }
                }
                else{
                    vector<Item*> stock = Items::getAllPossibleItems();
                    while (stock.size() > 5){
                        stock.erase(stock.begin() + (rand() % stock.size()));
                    }
                    int choice = promptUser(view::getNames(stock), view::getdescs(stock));
                    Item* a = stock[choice];
                    if (auto b = dynamic_cast<Weapon*>(a)){
                        if (dynamic_cast<Melee*>(b)) p1.setMelee(b);
                        else if (dynamic_cast<FireArm*>(b)) p1.setfirearm(b);
                    }
                    else{
                        p1.takeInInv(a);
                    }
                }
            }
            beatengame += 1;
        }
        else if (beatengame == 1){
            if (promptUser({"singleplayer", "multiplayer"}, {}) == 2)
            MultiplayerCombat();
            else goto singleplayer;
        }
        if (utils::promptUser({"yes", "no"}, {"Would you like to play again? "}) == 2){
            utils::slowPrint(utils:: roll(20) ? "Thank you for playing with me! " : "Thank you for playing IUST! ");
            Sleep(500);
            break;
        }
    }

    // cout << p1.getname();
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
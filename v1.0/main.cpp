#include <iostream>
#include <typeinfo>
#include "multi.hpp"
using namespace std;
using namespace utils;


const int PART = -1;
const int UNLOCK = -1;
int main(){

    srand(time(0));
    static int beatengame;
    if (beatengame > 100 || beatengame < 0) beatengame = 0;
    bool multi_unlocked = beatengame > 0;
        if (UNLOCK != -1) multi_unlocked = true;
    while (true){
        int balance = 0;
        if (multi_unlocked){
            singleplayer: 
            Player p1 = Player("You", 12, "male", 1, 40, 1, {Items::getAllPossibleItems()[0]}, "", "");
            p1.setMelee(dynamic_cast<Weapon*>(Items::getAllPossibleItems()[8]));
            p1.setfirearm(dynamic_cast<Weapon*>(Items::getAllPossibleItems()[6]));
            if (roll(30)) p1.setfirearm(dynamic_cast<Weapon*>(Items::getAllPossibleItems()[7]));
            for (int i = 0; i < 9; i++){
                slowPrintPrompts(popNextPrompts());
                int n = roll(3) + roll(3);
                if (i < 3){
                    while(n == 2){
                        n = roll(3) + roll(3);
                    }
                }
                if (PART != -1) n = PART;
                if (n == 0){
                    //zombie, normal or jugger or ghosty
                    Enemy* enemy;
                    enemy = roll(3) ? Enemies::gethusk(p1.getLVL(), p1.getluck(), p1.getFireArm()->getname()) : roll(2) ? Enemies::getghoul(p1.getLVL(), p1.getluck()) : Enemies::getjug(p1.getLVL(), p1.getluck());
                    slowPrint("\nYou are about to fight a " + enemy->getname());               
                    Sleep(1000);     
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
                    HumanEnemy* enemy = dynamic_cast<HumanEnemy*>(Enemies::getnerd(p1.getLVL(), p1.getluck()));
                    enemy->setfirearm(dynamic_cast<Weapon*>(Items::getAllPossibleItems()[9]));
                    enemy->setMelee(dynamic_cast<Weapon*>(Items::getAllPossibleItems()[8]));
                    
                    slowPrint("You are about to fight a " + enemy->getname());               
                    Sleep(1000);
                    Combat combat(&p1, enemy);
                    p1.updateRelics(); //updated tokens too
                    if (combat.gameloop()){
                        slowPrint("You lost! May you succeed in some other endeavor.\n");
                        Sleep(1000);
                    }
                }
                else{
                    cls();
                    vector<Item*> stock = Items::getAllPossibleItems();
                    while (stock.size() > 7){
                        stock.erase(stock.begin() + (rand() % stock.size()));
                    }
                    string str = "moments later, a pair of glowing ";
                    str.append((utils::roll(100) ? "" : "eye"));
                    str.append( "balls emerge from the dark. You can't help but stare and fret. At this point, running away would only make it angrier. Whatever it is ");
                    while (p1.getInv().size() < 5 && balance > 49){
                        vector<string> names = view::getNames(stock);
                        names.push_back("exit");
                        vector<vector<string>> descs1 = view::getvv(stock);
                        vector<vector<string>> descs2 = view::getvv(stock);
                        vector<vector<string>> descs3 = view::getvv(stock);
                        descs1.push_back({"Business Dawg sells no melee weapons. Too 'classy' for that stuff.", " Although, if you're lucky, Business Dawg may be looking to sell some cool sticks he found to collectors. "});
                        descs2.push_back({"Business Dawg has no concept of money. He only seems to like the shape of the number '50' on the dollar bills. "});
                        descs3.push_back({"Business Dawg is seen in many places running a store, strangely with a different hat each time. Although he insists he is not and hasn't heard of those other Dawgs."});
                        vector<vector<string>> descs = roll(3) ? descs1 : roll(2) ? descs2 : descs1;
                        int choice = promptUser(names, {"You come across a dark alleyway, like many others you've seen in your lifetime.","Or so it seemed at first... ", str, "As you stay still, waiting for your inevitable death, You see a hat come into the light...", "\"~~hElLo ThEre~~! Welcome to Business Dawg's accord!\"", "What can BusinessDawg get you today? ", "Balance: " + to_string(balance)}, descs);
                        if (choice == names.size()) break;
                        balance -= 50;
                        Item* a = stock[choice];
                        if (auto b = dynamic_cast<Weapon*>(a)){
                            if (dynamic_cast<Melee*>(b)) p1.setMelee(b);
                            else if (dynamic_cast<FireArm*>(b)) p1.setfirearm(b);
                        }
                        else{
                            p1.takeInInv(a);
                        }
                    }
                    if (balance == 0) utils::slowPrint("You have no money left. Seeing this, Business Dawg immediately prompts you to leave. \n");
                    else if (p1.getInv().size() >= 5)utils::slowPrint("Your inventory is full. Seeing this, Business Dawg throws you out of his shop.\n");
                }
            }
            beatengame += 1;
        }
        else if (beatengame >= 1){
            if (promptUser({"singleplayer", "multiplayer"}, {}) == 2)
                MultiplayerCombat();
            else goto singleplayer;
        }
        if (utils::promptUser({"yes", "no"}, {"Would you like to play again? "}) == 2){
            utils::slowPrint(utils::roll(20) ? "Thank you for playing with me! " : "Thank you for playing IUST! ");
            Sleep(500);
            break;
        }
    }
}
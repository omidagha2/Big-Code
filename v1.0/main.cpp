#include <iostream>
#include <typeinfo>
#include "multi.hpp"
using namespace std;
using namespace utils;

//devtools
//1: zombie attack  2: humanenemy (fsm) attack  3: the final boss
const int PART = -1;
const int UNLOCK = -1;

const int RELICSCOUNT = 7;

int main()
{
    for (int i = 0; i < RELICSCOUNT; i++) relics[i] = false;
    int seed;
    cls();
    int seedchoice = promptUser({"yes", "no (use time)"}, {"Would you like to seed? "});
    if (seedchoice == 1) {
        cin >> seed;
    }
    else{
        seed = time(0);
    }
    srand(seed);
    cout << "\nseed is: \n" << seed;
    Sleep(2000);
    cls();
    bool multi_unlocked = false;
    if (UNLOCK != -1)
        multi_unlocked = true;
    while (true)
    {
        int balance = 0;
        if (!multi_unlocked)
        {
        singleplayer:
            string boyname;
            slowPrintPrompts({"There's a young boy, sleeping peacefully in a bed. What's the boy's name? "});
            cin >> boyname;
            int choice = promptUser({"Pancakes", "Peanut butter sandwiches"}, {"What's the boy's favorite food?"}, {});
            Sleep(300);
            cls();
            string fav_food = choice == 1 ? "Pancakes" : "Peanut butter sandwiches";

            slowPrintPrompts({"You wake up from a refreshing sleep.", "It's an unusually sensual morning.", "The curtains are not drawn. Maybe that's why you slept so well.", "\n", "You make your way down to the living room. On the table, there's a plate of " + fav_food + "! Your favorite breakfast! You take one and save it for later, ood things should not be rushed.", "There's also a piece of paper on the table. Unfortunately, you can't read.", "\n", "You make your way to the couch to watch your favorite cartoon. On your way there, you notice a horrid smell.", "You investigate further. You find the source of the smell must be in the garage. ", "You go to the garage, as unexpecting as possible. Once you get there, you find the source of the smell is~",".",".",".", "~A FREAKING ZOMBIE! which is actually something you knew. It's been rotting away here for as long as you can remember.", "However, this time you notice something new. By the side of the rotting body, there's your favorite childhood toy! The Amazing Laser Gun! You thought it was broken! ", "You pick it up. A rush of memories you've had with it hits you. All the fun, the adventure...","Is this what life is supposed to be? ", "You are inspired. You put the gun in your pocket. You also grab the baseball bat. You go to the front door, and leave the house for the first time in forever, looking for some adventure! "});
            waitForInpt();

            slowPrint("A bit later, you make your first encounter of the cruwl real world...");
            Sleep(800);

            Player p1 = Player("You", 12, "male", 1, 40, 1, {Items::getAllPossibleItems()[0]}, "", "");
            p1.setMelee(dynamic_cast<Weapon *>(Items::getAllPossibleItems()[8]));
            p1.setfirearm(dynamic_cast<Weapon *>(Items::getAllPossibleItems()[6]));
            if (roll(30))
                p1.setfirearm(dynamic_cast<Weapon *>(Items::getAllPossibleItems()[7]));
            for (int i = 0; i < 20; i++)
            {   
                //events
                if (i == 3){
                    //shop 1
                    nextPrompts.push_back("You make your way out of the area. You are now in the city's main street, one of those you'd expect to be filled to the brim with people. However, it's dead silent.");
                    cls();
                    vector<Item *> stock = Items::getAllPossibleItems();
                    while (stock.size() > 7)
                    {
                        stock.erase(stock.begin() + (rand() % stock.size()));
                    }
                    string str = "moments later, a pair of glowing ";
                    str.append((roll(100) ? "" : "eye"));
                    str.append("balls emerge from the dark. You can't help but stare and fret. At this point, running away would only make it angrier. Whatever it is ");
                    while (p1.getInv().size() < 5 && balance > 49)
                    {
                        vector<string> names = view::getNames(stock);
                        names.push_back("exit");
                        vector<vector<string>> descs1 = view::getvv(stock);
                        vector<vector<string>> descs2 = view::getvv(stock);
                        vector<vector<string>> descs3 = view::getvv(stock);
                        descs1.push_back({"Business Dawg sells no melee weapons. Too 'classy' for that stuff.", " Although, if you're lucky, Business Dawg may be looking to sell some cool sticks he found to collectors. "});
                        descs2.push_back({"Business Dawg has no concept of money. He only seems to like the shape of the number '50' on the dollar bills. "});
                        descs3.push_back({"Business Dawg is seen in many places running a store, strangely with a different hat each time. Although he insists he is not and hasn't heard of those other Dawgs."});
                        vector<vector<string>> descs = roll(3) ? descs1 : roll(2) ? descs2
                                                                                  : descs1;
                        int choice = promptUser(names, {"You come across a dark alleyway, like many others you've seen in your lifetime.", "Or so it seemed at first... ", str, "As you stay still, waiting for your inevitable death, You see a hat come into the light...", "\"hElLo ThEre! WeLcOmE To Business Dawg's **BaRk MaRkEt!**\"", "\nWhat can BusinessDawg get you? ", "Balance: " + to_string(balance)}, descs);
                        if (choice == names.size())
                            break;
                        balance -= 50;
                        Item *a = stock[choice];
                        if (auto b = dynamic_cast<Weapon *>(a))
                        {
                            if (dynamic_cast<Melee *>(b))
                                p1.setMelee(b);
                            else if (dynamic_cast<FireArm *>(b))
                                p1.setfirearm(b);
                        }
                        else
                        {
                            p1.takeInInv(a);
                        }
                    }
                    if (balance == 0)
                        slowPrint("You have no money left. Seeing this, Business Dawg immediately prompts you to leave. \n");
                    else if (p1.getInv().size() >= 5)
                        slowPrint("Your inventory is full. Seeing this, Business Dawg throws you out of his shop.\n");
                }
                else if (i == 6){
                    //cute snake
                    int choice = promptUser({},{"As you progress along a sidewalk, you find a strange creature sitting on the other side of the road. ", "(un)carefully crossing the road, You get a better look at the creature. It's the most adorable thing you've ever seen in your life, whatever it is.", "Will you give in to the urge to pet him? "}, {{"The shiny yellow eyes make you grasp your breath. It desperately wants your pet.", "If it was hard before, it's nearly impossible not to now. "}, {"What if it;s contaminated?", "or worse, what if it's a snake? Is this what they look like? "}});
                    if (choice == 1){
                        relics[0] = true;
                        slowPrintPrompts({"The creature bits your hand and shoots a fast-paced dense liquid into your left eye, fleeing away immediately after.", "Your sight when attacking with a melee weapon is compromised. Fortunately you can aim guns with your other eye."});
                    }
                    else{
                        slowPrintPrompts({"You ignore the cutest thing you've seen in your life, and keep on walking. "});
                    }
                    Sleep(1000);
                }
                else if (i == 9){
                    //shop 2
                    nextPrompts.push_back("You make your way out of the main street. You are now in Bangalore Forest, a shortcut to the outskirts your dad told you about. ");
                    cls();
                    vector<Item *> stock = Items::getAllPossibleItems();
                    while (stock.size() > 7)
                    {
                        stock.erase(stock.begin() + (rand() % stock.size()));
                    }
                    //string for... easter egg
                    string str = "";
                    str.append((roll(100) ? "" : "eye"));
                    str.append("balls");
                    while (p1.getInv().size() < 5 && balance > 49)
                    {
                        vector<string> names = view::getNames(stock);
                        names.push_back("exit");
                        vector<vector<string>> descs1 = view::getvv(stock);
                        //random exit option prompts
                        descs1.push_back({"You ask the Dawg why he's wearing a different hat. ", "\"WhAt Do YoU MeAn?\", says the Business Dawg, claiming this is the only hat he has."});
                        vector<vector<string>> descs = descs1;
                        //prompt for shop
                        int choice = promptUser(names, {"The forest's path leads you deep inside it. You are feel like you're sieged by more trees every step. ","after a few minutes of exploring, you come across a once lovely shed. Now, probably a murderer's residence. ", "The eeriness is complemented by the creaking door swinging due to the wind.  ", "You are extremely tired. it's also almost past your bedtime, and it's necessary you sleep, so you have no choice but to go in.", "You half expect immediate death by cleaver. Instead, you find a Dawg donning a monocle. ","\"CaRe To BrOwSe SoMe RaRe FiNdS?\"", "\nWhat can Business Dawg get you today? ", "Balance: " + to_string(balance)}, descs);
                        if (choice == names.size())
                            break;
                        balance -= 50;
                        Item *a = stock[choice];
                        if (auto b = dynamic_cast<Weapon *>(a))
                        {
                            if (dynamic_cast<Melee *>(b))
                                p1.setMelee(b);
                            else if (dynamic_cast<FireArm *>(b))
                                p1.setfirearm(b);
                        }
                        else
                        {
                            p1.takeInInv(a);
                        }
                    }
                    if (balance == 0)
                        slowPrint("You have no money left. Seeing this, Business Dawg immediately prompts you to leave. \n");
                    else if (p1.getInv().size() >= 5)
                        slowPrint("Your inventory is full. Seeing this, Business Dawg throws you out of his shop.\n");
                }
                else if (choice == 15){
                    //laser gun upgrade
                    if (p1.getFireArm()->getname() == "Laser Gun"){
                        slowPrint("As you explore the forest, you come across a peculiar blue object. You don't know what it is, but it looks like it fits perfectly on your laser gun.\nYou attach it to your gun. Your laser gun now freezes enemies! Freezing an enemy reduces their tokens by one. \nIt also comes with a full refill for ammo");
                        p1.setfirearm(dynamic_cast<Weapon*>(Items::getAllPossibleItems()[7]));
                        waitForInpt();
                    }
                }
                else if (choice == 12){
                    //popsicle man
                    int choice = promptUser({"trade everything for ice creams", "don't take the deal"}, {"You find a lost man, standing under a tree while holding 5 ice creams. ", "As you approach the man he lights up. \"PLEASE! PLEASE TAKE IT!\" he says. ", "You interpret his saying as follows: You can take a bunch of ice cream, free of charge. However, you have to take them all. ", "Will you take his offer? "}, {{"5 ice creams is the most you've ever seen together. Way too tempting to refuse. "}, {"maybe taking ice cream from a stranger is not a good idea"}});
                    if (choice == 1){
                        slowPrintPrompts({"The man thanks you (not normally) for lifting his burden of having to deal with a bunch of meting ice creams. ", "He then happily wanders off, free of ice cream. "});
                        p1.setInv({Items::getAllPossibleItems()[2], Items::getAllPossibleItems()[2], Items::getAllPossibleItems()[2], Items::getAllPossibleItems()[2], Items::getAllPossibleItems()[2]});
                        waitForInpt();
                    }
                    else{
                        slowPrint("You ignore the crazy man and walk away.\n A few seconds later you hear a loud \"NOOOOOOOOOOoooooo\", weakening until the sayer runs out of breath. Those ice creams were definitely cursed. ");
                    waitForInpt();
                    }
                }
                else if (choice == 18){
                    //shop 3
                    nextPrompts.push_back("Finally, you make it out of the forest. You are greeted with the sight of a beautiful outskirts area. You feel like, in your past lives, you've made many good memories here. ");
                    cls();
                    vector<Item *> stock = Items::getAllPossibleItems();
                    while (stock.size() > 7)
                    {
                        stock.erase(stock.begin() + (rand() % stock.size()));
                    }
                    while (p1.getInv().size() < 5 && balance > 49)
                    {
                        vector<string> names = view::getNames(stock);
                        names.push_back("exit");
                        vector<vector<string>> descs2 = view::getvv(stock);
                        //random exit option prompts
                        descs2.push_back({"\"HaVe YoU SeEn My CoSiNs?\" says the Dawg... maybe they were different 50 loving Dawgs all along. ", "S"});
                        vector<vector<string>> descs = descs2;
                        //prompt for shop
                        int choice = promptUser(names, {"In the middle of a flat landscape, there's a large tent. You can make out from the faded colors and deteriorating shape that it once belonged to a circus. ", "The shadows cast by the sun don't match what you'd expect. They almost look like silhouettes of people, performing. ", "The air carries the withered echo of a distant circus band, both enchanting and terrifying.", "You walk to the entrance without thinking. Curiosity beats your common sense. or, maybe your mind is not in your control... ", "\nalthough the tent is completely empty, it feels crowded. Counting it off as just a feeling, you feel a ghostly whisper by your ear. It seems like you can make out some words from it:", "\"WoUlD YoU LiKe SoMe WaReS? \"", "\nWhat can Business Dawg get you today? ", "Balance: " + to_string(balance)}, descs);
                        if (choice == names.size())
                            break;
                        balance -= 50;
                        Item *a = stock[choice];
                        if (auto b = dynamic_cast<Weapon *>(a))
                        {
                            if (dynamic_cast<Melee *>(b))
                                p1.setMelee(b);
                            else if (dynamic_cast<FireArm *>(b))
                                p1.setfirearm(b);
                        }
                        else
                        {
                            p1.takeInInv(a);
                        }
                    }
                    if (balance == 0)
                        slowPrint("You have no money left. Seeing this, Business Dawg immediately prompts you to leave. \n");
                    else if (p1.getInv().size() >= 5)
                        slowPrint("Your inventory is full. Seeing this, Business Dawg throws you out of his shop.\n");

                }
                slowPrintPrompts(popNextPrompts());
                int n = roll(4);
                n = PART == -1 ? n : PART;
                if (n == 0)
                {
                    // zombie, normal or jugger or ghosty
                    Enemy *enemy;
                    enemy = roll(3) ? Enemies::gethusk(p1.getLVL(), p1.getluck(), p1.getFireArm()->getname()) : roll(2) ? Enemies::getghoul(p1.getLVL(), p1.getluck())
                                                                                                                        : Enemies::getjug(p1.getLVL(), p1.getluck());
                    slowPrint("\nYou are about to fight a " + enemy->getname());
                    Sleep(1000);
                    Combat combat(&p1, enemy);
                    p1.updateRelics();
                    if (combat.gameloop())
                    {
                        slowPrint("You lost! May you succeed in later endeavors.\n");
                        Sleep(1000);
                        exit(0);
                    }
                    else
                    {
                        slowPrint("You won! as a reward, you get: \n+50 coins");
                        balance += 50;
                        p1.setlvl(p1.getLVL() + 1);
                        if (roll(4)) p1.setluck(p1.getluck() + 1);
                        if (roll(20))
                        {
                            slowPrint("you found a ~relic~ How exciting! \nHere's a list of all the relics you have: \n");
                            int i = rand() % RELICSCOUNT - 1;
                            relics[i + 1] = true;
                            view::showrelics;
                        }
                    }
                }
                else if (n == 1)
                {
                    // human enemy
                    HumanEnemy *enemy = dynamic_cast<HumanEnemy *>(Enemies::getnerd(p1.getLVL(), p1.getluck()));
                    enemy->setfirearm(dynamic_cast<Weapon *>(Items::getAllPossibleItems()[9]));
                    enemy->setMelee(dynamic_cast<Weapon *>(Items::getAllPossibleItems()[8]));

                    slowPrint("You encountered a " + enemy->getname() +"!");
                    Sleep(1000);
                    Combat combat(&p1, enemy);
                    p1.updateRelics(); // updated tokens too
                    if (combat.gameloop())
                    {
                        slowPrint("You lost! May you succeed in some other endeavor.\n");
                        Sleep(1000);
                        exit(0);
                    }
                }
            }
            //outside of the for
            //they should add a button to navigate between scopes
            bool fb = true;
            vector<string> improudofthis = {"After all that struggle, you're finally there. This is the spot.", "The beautiful sun is shining in the perfect angle.", "You sit down for a second to appreciate the view.", "a distant valley spreads out like a big green blanket, with hills rolling like waves under a saturated sky. You feel relief. ", "You rest there for a while, looking at the blue sky.", "You see many clouds in the sky. They each take a different shape if you look the right way. ", "That one looks like a fluffy cotton ball.", "Another like a soft pillow waiting to be dreamt on. ", "One even looks like a fish, swimming around in the ocean. ", "\nthe sky is promising you adventure as far as the eye can see; ", "But you were so sure that this would be the end of your adventure. ", "As you start contemplating, there immerges a Huge zombie from horizon. It approaches you...", "Press any key to continue"};
            slowPrintPrompts(improudofthis);
            waitForInpt();
            if (p1.haspbs()){//he likes his imagination and genuinely had fun
                int choice = promptUser({"give them the peanut butter sandwich", "eat the peanut butter sandwich"}, {"You panic.", "You're scared this might be the end of it all, just before you found more adventure.", "Fighting the zombie seems impossible to survive. You try to compromise, find a different way. ", "suddenly, you find you have a slice of peanut butter sandwich"},{{"What f it's just hungry? "}, {"Might as well enjoy one last good thing. "}});
                if (choice == 1){
                    slowPrintPrompts({"You panic. ","You take out the sandwich and offer it to the zombie."," The zombie in response throws a bite, aiming for your hand, but misses it. However, he catches the peanut butter sandwich.", "Realizing that, he stops. Now, he looks panicked. ", "He takes his eyes off of you. He goes to the highest spot of the hill, sits down, and smiles a horrifying grin. A few moments later, there's a very loud gurgling noise.", "He explodes.~","~ You think he was probably allergic to nuts."});
                    fb = false;
                    waitForInpt();
                    slowPrintPrompts({"With that part of you gone, now you truly feel relief. You sit back, look at the sky... ", "\n", "and eat the peanut butter sandwich."});
                    waitForInpt();
                }
                else{
                    slowPrint("You try to eat the sandwich as fast as you can. But, that would waste many good seconds, so you stop. You get up, take out your weapons, and fight with all your might!\n");
                    waitForInpt();
                }
            }
            if (fb){
                cls();
                HumanEnemy *enemy = roll(6) ? dynamic_cast<HumanEnemy *>(Enemies::getmother(p1.getLVL(), p1.getluck())) : dynamic_cast<HumanEnemy *>(Enemies::getmirth(p1.getLVL(), p1.getluck()));
                    enemy->setfirearm(dynamic_cast<Weapon *>(Items::getAllPossibleItems()[9]));
                    enemy->setMelee(dynamic_cast<Weapon *>(Items::getAllPossibleItems()[8]));
                    cls();
                    slowPrint("You encountered a " + enemy->getname() +"!");
                    slowPrint("This is the final boss of the game. Win to unlock something cool! ");
                    Sleep(1000);
                    Combat combat(&p1, enemy);
                    p1.updateRelics(); // updated tokens too
                    if (combat.gameloop())
                    {
                        slowPrint("You lost! May you succeed in some other endeavor.\n");
                        Sleep(1000);
                        exit(0);
                    }
            slowPrint("With that part of you gone, you can now truly rest. You lay back down, look up at the sky, and imagine your head on the softest cloud, dreaming over and over again...");
            waitForInpt();
            }
            cls();
            
            if (!multi_unlocked) slowPrint("You unlocked multiplayer! ");
            multi_unlocked = true;
        }
        else if (multi_unlocked)
        {
            if (promptUser({"singleplayer", "multiplayer"}, {}) == 2)
                MultiplayerCombat();
            else
                goto singleplayer;
        }
        if (promptUser({"yes", "no"}, {"Would you like to play again? "}) == 2)
        {
            slowPrint(roll(20) ? "Thank you for playing with me! " : "Thank you for playing IUST! ");
            Sleep(500);
            break;
        }
    }
}
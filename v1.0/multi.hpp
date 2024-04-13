#include "items.hpp"
using namespace std;

class MultiplayerCombat
{
private:
    Player boy;
    Player girl;
    bool turnOfBoy; // True if it's the boy's turn, false if it's the girl's

public:
    MultiplayerCombat() : turnOfBoy(false)
    {
        for (int i = 0; i < 7; i++)
        {
            relics[i] = 0;
        }
        utils::slowPrintPrompts({"There's a boy playing with some toys.", "He has an awesome laser gun.", "What is his name? How old is he? "});
        string name;
        int age;
        cin >> name >> age;
        boy = Player(name, age, "male", 1, 40, 2, {Items::getAllPossibleItems()[1], Items::getAllPossibleItems()[1], Items::getAllPossibleItems()[1], Items::getAllPossibleItems()[1], Items::getAllPossibleItems()[1]});
        boy.setMelee(dynamic_cast<Weapon *>(Items::getAllPossibleItems()[6]));
        utils::slowPrintPrompts({"Someone rings the doorbell.", "The boy's mom opens the door. It's a cheerful girl! She seems to have come for a playdate. Although, for some reason she brought over a baseball bat.", "What is her name? How old is she? "});
        cin >> name >> age;
        girl = Player(name, age, "female", 1, 40, 2, {Items::getAllPossibleItems()[0], Items::getAllPossibleItems()[0], Items::getAllPossibleItems()[0], Items::getAllPossibleItems()[0], Items::getAllPossibleItems()[0]});
        girl.setMelee(dynamic_cast<Weapon *>(Items::getAllPossibleItems()[8]));
        girl.setCombatTokens(1);
        boy.setCombatTokens(1);
        startCombat();
    }

    //initiates combat after information is gathered. 
    void startCombat()
    {
        while (boy.isAlive() && girl.isAlive())
        {
            displayTurnPrompt();
            turnOfBoy = !turnOfBoy;
            if (!boy.isAlive() || !girl.isAlive())
            {
                announceWinner();
                break;
            }
        }
    }

    //prompts the player whose turn it is accordingly. takes input and does action too.
    void displayTurnPrompt()
    {
        Player *turnedPlayer = (turnOfBoy ? &boy : &girl);
        Player *unturnedplayer = (!turnOfBoy ? &boy : &girl);
        nextPrompts.push_back(turnedPlayer->getname() + "'s turn. Get ready for some action!\n");
        nextPrompts.push_back(turnOfBoy ? boy.getname() + " readies his laser gun!" : girl.getname() + " waves her sparkly magic wand(bat)!");
        int choice = utils::promptUser({"Attack", "Use consumable"}, utils::popNextPrompts());
        if (choice == 1)
        {
            int score = turnOfBoy ? (turnedPlayer->atkBarGun(0)) : (turnedPlayer->atkBarMelee(0));
            unturnedplayer->getAttacked(turnedPlayer->getMelee(), score / 3.0);
        }
        else
        {
            int choice = promptUser(view::getNames(turnedPlayer->getInv()), {}, view::getvv(turnedPlayer->getInv()));
            turnedPlayer->consumeConsumable(turnedPlayer->getInv()[choice]);
        }
    }

    //announces the winner. 
    void announceWinner()
    {
        if (!boy.isAlive())
        {
            utils::slowPrint(girl.getname() + " wins with her unstoppable magic powers!");
        }
        else if (!girl.isAlive())
        {
            utils::slowPrint(boy.getname() + " wins with his awesome laser gun skills!");
        }
    }
};
#include "objects2.hpp"

class Combat
{
    Player *you;
    Entity *foe;

public:
    Combat(Player *player, Enemy *target)
    {
        you = player;
        foe = target;
    }
    Player *getPlayer() { return you; }
    Entity *getFoe() { return foe; }

    //adds attack prompt to nextPrompts
    void pushPrompt()
    {
        nextPrompts.push_back(foe->getname() + " attacked you for " + to_string(foe->getDMG()) + " hp!");
    }

    //implementation of enemy's turn
    int foeAttackYou()
    {
        if (auto zomb = dynamic_cast<Zombie *>(foe))
        {
            you->takeIntDamage(foe->getDMG());
            pushPrompt();
        }
        else if (auto man = dynamic_cast<HumanEnemy *>(foe))
        { // fsm here
            runfsm();
        }
    }

    // implementation of player's turn
    int attackFoe()
    {
        you->setCombatTokens(you->getMaxCombatTokens());

        // prompt, eventually use item.
        while (you->getCombatTokens() > 0)
        {
            utils::cls();
            vector<string> nps = utils::popNextPrompts();
            nps.push_back(foe->getname() + " is looking " + (dynamic_cast<Zombie *>(foe) != nullptr ? "hungry! " : "angry! "));
            nps.push_back(foe->getRandomPrompt());
            vector<string> precombatprompt = {"You have " + to_string(you->getCombatTokens()) + " tokens left.", "What will you do? "};
            for (string p : precombatprompt) //
            {
                nps.push_back(p);
            }
            int choice = utils::promptUser({"Attack with a gun", "Attack with a melee weapon", "Use a consumable", "examine yourself", "examine enemy", "end turn"}, nps);
            while (true)
            {
                if (choice == 1)
                {
                    string pp1, pp2;
                    pp1 = (you->getFireArm())->getname();
                    auto gun = (dynamic_cast<FireArm *>(you->getFireArm()));
                    pp2 = (gun->getinfo());
                    // show weapon stats and desc. first stats, then choices, then slowprint desc.
                    if (gun->getAmmo() == 0)
                    {
                        nextPrompts.push_back("This weapon has no ammo. ");
                        break;
                    }
                    gun->decreaseAmmo();
                    int yn = utils::promptUser({"yes", "no"}, {pp1, pp2}, {(you->getFireArm())->getDesc(), {"You look into " + foe->getname() + "'s eyes.", "Among all the chaos, you can still find some life.", "You consider not attacking, but your cause is still unknown. Is it mercy, or the urge to maximize damage?"}});
                    if (yn == 2)
                        break;
                    if (you->getFireArm()->getTokenUse() > you->getCombatTokens())
                    {
                        utils::slowPrint("You don't have enough tokens to use this weapon.");
                        break;
                    }
                    else
                    {
                        you->setCombatTokens(you->getCombatTokens() - you->getFireArm()->getTokenUse());
                    }
                    int score = you->atkBarGun(0);

                    cout << "  x" << score / 3.0 << endl;
                    Sleep(500);
                    foe->getAttacked(you->getFireArm(), score / 3.0);
                    you->setCombatTokens(0);
                    // nextPrompts.push_back("You dealt " + to_string(foe->calculateDmgWpn(you->getFireArm())) + " damage to " + foe->getname());
                    break;
                }
                else if (choice == 2)
                {
                    string pp1, pp2, pp3;
                    pp1 = (you->getMelee())->getname();
                    auto melptr = (dynamic_cast<Melee *>(you->getMelee()));
                    pp2 = (melptr->getinfo());
                    int yn = utils::promptUser({"yes", "no"}, {pp1, pp2}, {(you->getMelee())->getDesc(), {"You look into " + foe->getname() + "'s eyes.", "Despite the chaos, you can still see there's some life in there.", "You consider not attacking, but your cause is still unknown. Is it mercy, or the urge to maximize damage?"}});
                    if (yn == 2)
                        break;
                    if (you->getMelee()->getTokenUse() > you->getCombatTokens())
                    {
                        utils::slowPrint("You don't have enough tokens to use this weapon.");
                        break;
                    }
                    else
                    {
                        you->setCombatTokens(you->getCombatTokens() - you->getMelee()->getTokenUse());
                    }
                    int score = you->atkBarMelee(0);
                    cout << "  x" << score / 10.0;
                    Sleep(500);
                    foe->getAttacked(you->getMelee(), score / 10.0);
                    you->setCombatTokens(0);
                    break;
                    // nextPrompts.push_back("You dealt " + to_string(foe->calculateDmgWpn(you->getMelee())) + " damage to " + foe->getname());
                }
                else if (choice == 3)
                {
                    ItemBunch consumables;
                    for (Item *i : you->getInv())
                    {
                        if (auto a = dynamic_cast<Consumable *>(i))
                        {
                            consumables.addItem(i);
                        }
                    }
                    Item *cons_choice = consumables.displayAndChooseItem();
                    if (cons_choice == nullptr)
                    {
                        nextPrompts.push_back("You have no items available. ");
                        break;
                    }
                    you->consumeConsumable(cons_choice);
                    you->setCombatTokens(you->getCombatTokens() - 1);
                    break;
                }
                else if (choice == 4)
                    nextPrompts.push_back(view::info(foe));

                else if (choice == 5)
                {
                    nextPrompts.push_back(view::info(you));
                    for (int i = 0; i < view::showrelics().size(); i++)
                    {
                        nextPrompts.push_back(view::showrelics()[i]);
                    }
                }
                else
                    you->setCombatTokens(0);
                break;
            }
        }
    }

    //fsm logic for human enemy
    void runfsm()
    {
        HumanEnemy *enemy = dynamic_cast<HumanEnemy *>(foe);
        if (!enemy)
            return;
        enemy->setCurrentState(HumanEnemy::State::Entry);
        enemy->setCombatTokens(3 - enemy->isfrozen());
        int iterations = 0;
        const int max_iterations = 3;

        while (iterations <= max_iterations)
        {
            nextPrompts.push_back(enemy->getname() + " has moved to the " + enemy->getStateStr() + " State. That means " + enemy->getStateDesc());
            // Entry State: Calculate best weapon and reserve tokens for it.
            if (enemy->getCurrentState() == HumanEnemy::Entry)
            {
                Weapon *bestWeapon = enemy->calculateBestWeapon(you);
                enemy->settabw(bestWeapon ? enemy->getCombatTokens() - bestWeapon->getTokenUse() : enemy->getCombatTokens());
                if (enemy->hpFullPercent() < 25)
                    enemy->setCurrentState(HumanEnemy::DangerouslyLowHp);
                else if (enemy->hpFullPercent() < 60)
                    enemy->setCurrentState(HumanEnemy::KindaLowHp);
                else
                    enemy->setCurrentState(HumanEnemy::HpFine);
            }

            // DangerouslyLowHp State: Use best healing consumable.
            else if (enemy->getCurrentState() == HumanEnemy::DangerouslyLowHp)
            {
                Consumable *bestHealing = enemy->findBestConsumableForUtilization(1);
                if (bestHealing && enemy->getCombatTokens() >= bestHealing->getTokenUse() + enemy->gettabw())
                {
                    bestHealing->apply(enemy);
                    nextPrompts.push_back(enemy->getname() + " used " + bestHealing->getname() + " and is now on " + to_string(enemy->getHp()));
                    enemy->usetokens(bestHealing->getTokenUse());
                }
                enemy->setCurrentState(HumanEnemy::AreThereTokens);
            }

            // KindaLowHp State: Use most effective healing consumable.
            else if (enemy->getCurrentState() == HumanEnemy::KindaLowHp)
            {
                Consumable *bestHealingCheap = enemy->findBestConsumableForUtilization(2); // Implement this to maximize effective healing
                if (bestHealingCheap && enemy->getCombatTokens() >= bestHealingCheap->getTokenUse() + enemy->gettabw())
                {
                    bestHealingCheap->apply(enemy);
                    nextPrompts.push_back(enemy->getname() + " used " + bestHealingCheap->getname() + " and is now on " + to_string(enemy->getHp()));
                    enemy->usetokens(bestHealingCheap->getTokenUse());
                }
                enemy->setCurrentState(HumanEnemy::Attack);
            }

            // HpFine State: Use best damage consumable.
            else if (enemy->getCurrentState() == HumanEnemy::HpFine)
            {
                Consumable *bestDamageCheap = enemy->findBestConsumableForUtilization(3);
                if (bestDamageCheap && enemy->getCombatTokens() >= bestDamageCheap->getTokenUse() + enemy->gettabw())
                {
                    bestDamageCheap->apply(you);
                    nextPrompts.push_back(enemy->getname() + " used " + bestDamageCheap->getname() + " on " + you->getname() + "! ");
                    enemy->usetokens(bestDamageCheap->getTokenUse());
                }
                enemy->setCurrentState(HumanEnemy::AreThereTokens);
            }

            // Attack State: Use best weapon.
            else if (enemy->getCurrentState() == HumanEnemy::Attack)
            {
                if (enemy->getCombatTokens() >= enemy->gettabw())
                {
                    enemy->attackWith(enemy->getbw(), you);
                    break;
                }
            }

            else if (enemy->getCurrentState() == HumanEnemy::AreThereTokens)
            {
                if (enemy->getCombatTokens() >= enemy->gettabw())
                {
                    enemy->setCurrentState(HumanEnemy::Entry);
                    iterations++;
                }
                else
                    enemy->setCurrentState(HumanEnemy::Attack);
            }

            if (iterations > max_iterations)
            {
                enemy->setCurrentState(HumanEnemy::Attack); // Force an attack if max iterations reached
            }
        }
    }

    //implementation of the game loop. also returns 1 if you (player) die.
    bool gameloop()
    { 
        bool turn = 1;
        while (foe->isAlive() && you->isAlive())
        {
            if (turn)
            {
                attackFoe();
            }
            else
            {
                foeAttackYou();
            }
            turn = !turn;
        }
        return (foe->isAlive());
    }
};

#include "objects2.hpp"


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
    Combat(Player* player, Enemy* target){you = player; foe = target;}
    Player* getPlayer(){return you;}
    Entity* getFoe(){return foe;}
    void pushPrompt(){
        nextPrompts.push_back(foe->getname() + " attacked you for " + to_string(foe->getDMG()) + " hp!");
    }
    int foeAttackYou(){
        if (auto zomb = dynamic_cast<Zombie*>(foe)){
            you->takeIntDamage(foe->getDMG());
            pushPrompt();
        }
        else if (auto man = dynamic_cast<HumanEnemy*>(foe)){//fsm here
            runfsm();
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
            int choice = utils::promptUser({"Attack with a gun", "Attack with a melee weapon", "Use a consumable", "examine yourself", "examine enemy"}, nps);
                if(choice== 1){
                //show weapon stats and desc. first stats, then choices, then slowprint desc.
                if ((dynamic_cast<FireArm*>(you->getFireArm()))->getAmmo() == 0){
                    nextPrompts.push_back("This weapon has no ammo. ");
                    break;
                }
                int yn = utils::promptUser({"yes", "no"}, /*stats*/{},{(you->getFireArm())->getDesc(), {"You look into " + foe->getname() + "'s eyes.", "Despite the chaos, you can still see there's some life in there.", "You consider not attacking, but your cause is still unknown. Is it mercy, or the urge to maximize damage?"}});
                if (yn == 2) break;
                int score = you->atkBarGun(0);
                cout <<"  x"<< score/6.0;
                Sleep(500);
                foe->getAttacked(you->getFireArm(), score/6.0);
                nextPrompts.push_back("You dealt " + to_string(foe->calculateDmgWpn(you->getFireArm())) + " damage to " + foe->getname());
                break;
                }
                else if (choice == 2){
                int yn = utils::promptUser({"yes", "no"}, /*stats*/{},{(you->getMelee())->getDesc(), {"You look into " + foe->getname() + "'s eyes.", "Despite the chaos, you can still see there's some life in there.", "You consider not attacking, but your cause is still unknown. Is it mercy, or the urge to maximize damage?"}});
                if (yn == 2) break;
                int score = you->atkBarMelee(0);
                cout <<"  x"<< score/10.0;
                Sleep(500);
                foe->getAttacked(you->getMelee(), score/10.0);
                nextPrompts.push_back("You dealt " + to_string(foe->calculateDmgWpn(you->getMelee())) + " damage to " + foe->getname());
                }
                else if (choice == 3){
                ItemBunch consumables;
                for (Item* i: you->getInv()){
                    if (auto a = dynamic_cast<Consumable*>(i)){
                        consumables.addItem(i);
                    }
                }
                Item* cons_choice = consumables.displayAndChooseItem();
                you->consumeConsumable(cons_choice);
                break;
                }
                else if (choice == 4)
                nextPrompts.push_back(view::info(foe));


                else{
                nextPrompts.push_back(view::info(you));
                for (int i = 0; i < view::showrelics().size(); i++){
                nextPrompts.push_back(view::showrelics()[i]);
                }
                }
        }
    }

    void runfsm(){
        HumanEnemy* enemy = dynamic_cast<HumanEnemy*>(foe);
        if (!enemy) return;
        enemy->setCurrentState(HumanEnemy::State::Entry);
        enemy->setCombatTokens(3 - enemy->isfrozen());
        int iterations = 0;
        const int max_iterations = 3;

        while (iterations <= max_iterations) {
            // Entry State: Calculate best weapon and reserve tokens for it.
            if (enemy->getCurrentState() == HumanEnemy::Entry) {
                Weapon* bestWeapon = enemy->calculateBestWeapon(you);
                enemy->settabw(bestWeapon ? enemy->getCombatTokens() - bestWeapon->getTokenUse() : enemy->getCombatTokens());
                if (enemy->hpFullPercent() < 25)
                    enemy->setCurrentState(HumanEnemy::DangerouslyLowHp);
                else if (enemy->hpFullPercent() >= 25 && enemy->hpFullPercent() < 90)
                    enemy->setCurrentState(HumanEnemy::KindaLowHp);
                else
                    enemy->setCurrentState(HumanEnemy::HpFine);
            }

            // DangerouslyLowHp State: Use best healing consumable.
            if (enemy->getCurrentState() == HumanEnemy::DangerouslyLowHp) {
                Consumable* bestHealing = enemy->findBestConsumableForUtilization(0); // Implement this to focus on healing
                if (bestHealing && enemy->getCombatTokens() >= bestHealing->getTokenUse() + enemy->gettabw()) {
                    bestHealing->apply(enemy);
                    enemy->usetokens(bestHealing->getTokenUse());
                }
                enemy->setCurrentState(HumanEnemy::Attack);
            }

            // KindaLowHp State: Use most effective healing consumable.
            if (enemy->getCurrentState() == HumanEnemy::KindaLowHp) {
                Consumable* bestHealingCheap = enemy->findBestConsumableForUtilization(1); // Implement this to maximize effective healing
                if (bestHealingCheap && enemy->getCombatTokens() >= bestHealingCheap->getTokenUse() + enemy->gettabw()) {
                    bestHealingCheap->apply(enemy);
                    enemy->usetokens(bestHealingCheap->getTokenUse());
                }
                enemy->setCurrentState(HumanEnemy::Attack);
            }

            // HpFine State: Use best damage consumable.
            if (enemy->getCurrentState() == HumanEnemy::HpFine) {
                Consumable* bestDamageCheap = enemy->findBestConsumableForUtilization(2); // Implement this to focus on damage
                if (bestDamageCheap && enemy->getCombatTokens() >= bestDamageCheap->getTokenUse() + enemy->gettabw()) {
                    bestDamageCheap->apply(you);
                    enemy->usetokens(bestDamageCheap->getTokenUse());
                    
                }
                if (enemy->getCombatTokens() < enemy->gettabw()) {
                    enemy->setCurrentState(HumanEnemy::HpFine);
                } else {
                    enemy->setCurrentState(HumanEnemy::Attack);
                }
            }

            // Attack State: Use best weapon.
            if (enemy->getCurrentState() == HumanEnemy::Attack) {
                if (enemy->getCombatTokens() >= enemy->gettabw()) {
                    enemy->attackWith(enemy->getMelee(), you);
                    break; // Attack and exit the loop
                }
            }

            iterations++;
            if (iterations > max_iterations) {
                enemy->setCurrentState(HumanEnemy::Attack); // Force an attack if max iterations reached
            }
        }
    }

    bool gameloop(){//returns 1 if you lose.
        bool turn = 1;
        while (foe->isAlive() && you->isAlive()){
            if (turn){
                attackFoe();
            }
            else{
                foeAttackYou();
            }
            turn = !turn;
        }
        return (foe->isAlive());
    }
};

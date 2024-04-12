#include "items.hpp"
#include "objects.hpp"
#include <conio.h>
#include <windows.h>
#include <algorithm>



namespace combat1 {
    class EnemyModel1 {
        HumanEnemy* self;
        Player* player;
        enum class State {
            Entry,
            Low_HP,
            Dangerously_Low_HP,
            HpFine,
            Low_STA,
            Check_Weapon,
            Use_Item,
            Attack
        };

        State current_state;

    public:
        EnemyModel1();
        ~EnemyModel1();
        static EnemyModel1 instance();
        void set(HumanEnemy* reference_ptr);
        void execute();
        void DLHP();
        static bool SortByV( ValuedComponent& i1,  ValuedComponent& i2);
        static bool SortByUP( ValuedComponent& i1,  ValuedComponent& i2);
        void attack(Player* player);
        int calculateDamage(Player* player, Weapon* weapon);
    };

    class CombatController {
        Entity* friendPTR;
        Entity* foePTR;

    public:
        static CombatController& GetInstance();
        static Entity* getFriendPTR();
        static Entity* getFoePTR();

    private:
        Entity* imp_getFriendPTR();
        Entity* imp_getFoePTR();
        void Imp_GameLoop();
    };



    EnemyModel1::EnemyModel1() : self(nullptr), player(nullptr), current_state(State::Entry) {}

    EnemyModel1::~EnemyModel1() {}

    EnemyModel1 EnemyModel1::instance() {
        static EnemyModel1 x;
        return x;
    }

    void EnemyModel1::set(HumanEnemy* reference_ptr) {
        self = reference_ptr;
    }

    void EnemyModel1::execute() {
      State state = this->current_state;
      if (state == State::Entry){
        self->hpFullPercent() < 25 ? current_state = State::Dangerously_Low_HP : self->hpFullPercent() < 90 ? current_state = State::Low_HP : current_state = State::HpFine;
      }
      else if (state == State::Dangerously_Low_HP){
        //maybe add optimizations to not sort again if not needed?
        vector<Consumable*> value_sorted_consumable_inv = self->getConsumablesInv();
        sort(value_sorted_consumable_inv.begin(), value_sorted_consumable_inv.end(), SortByV);
        //use the first one
      }
    }

    void EnemyModel1::DLHP() {
        // Implementation as provided in the question
    }

    bool EnemyModel1::SortByV(ValuedComponent& i1, ValuedComponent& i2) {
        return i1.getVal() > i2.getVal();
    }

    bool EnemyModel1::SortByUP( ValuedComponent& i1,  ValuedComponent& i2) {
        return i1.usePercent() > i2.usePercent();
    }

    void EnemyModel1::attack(Player* player) {
        player->takeDamage(self->getDMG());
    }

    int EnemyModel1::calculateDamage(Player* player, Weapon* weapon) {
        return self->getDMG();
    }

    CombatController& CombatController::GetInstance() {
        static CombatController combatInstance;
        return combatInstance;
    }

    Entity* CombatController::getFriendPTR() { return GetInstance().imp_getFriendPTR(); }

    Entity* CombatController::getFoePTR() { return GetInstance().imp_getFoePTR(); }

    Entity* CombatController::imp_getFriendPTR() { return friendPTR; }

    Entity* CombatController::imp_getFoePTR() { return foePTR; }

    void CombatController::Imp_GameLoop() {
        // Implementation as provided in the question
    }
}
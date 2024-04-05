#include "items.hpp"
#include "objects.hpp"
#include <conio.h>
#include <windows.h>
#include <algorithm>
// enemy combat fsm 1:
// this implementation allows each enemy to be in a certain enum state. in each rendition of the machine, the enemy
// checks what state it's in, then performs accordingly.

namespace utils{
    enum Color{
        ORANGE,
        RED,
        GREEN,
        BLUE,
        WHITE

    };
    void slowPrint(string prompt, Color color=WHITE, double char_delay_ms=100){
        for (char c: prompt){
            cout << c;
        }
    }
    void slowPrint(vector<string> prompts, Color color=WHITE, double char_delay_ms=100, double sentence_delay_ms=1000, string sentence_sep = "\n"){
        for (int i = 0; i < prompts.size(); i++){    
            for (char c: prompts[i]){
                cout << c;
                Sleep(char_delay_ms);
            }
            Sleep(sentence_delay_ms);
            if (i != prompts.size()) cout << sentence_sep;
        }
    }
    void cleanScreen(){

    }
}
namespace combat1
{
    #include "CombatStates2.hpp"
    class EnemyModel1
    {

        HumanEnemy *self;
        Player* player;
        //~~notes~~
        // tokens are spent changing equipped item.
        // maybe there can also be a lowHPandSTA state.
        enum class State
        {

            Entry,

            Low_HP, // checks if it has consumables that restore hp. if so, creates a list of the consumables and uses the one with the highest usepercentage.
                    //(use this for some other implementation)////the enemy doesn't go to this mode if it's only missing a few points of hp. so it's safe to say it won't be considering using any high percent low recovering items.
                    // the difference is here the enemy sorts the items based on usepercentage first, then healing value.

            Dangerously_Low_HP, // here they really want to use a hp recovering item. here, the amount restored also comes into play (the amount restored beyond what is effective doesn't count, like if it exeeds the enemy's hp limit)
                                // they sort it based on what can bring him up to / closest to 90 percent of their hp. if there are multiple best answers, uses the highest usepercent.

            HpFine, // enemy goes to this state if it doesn't enter any other states. maybe he instead uses some buffs, reloads a weapon, etc.

            Low_STA, // the enemy just uses what restores it's stamina closest to 90 percent.

            Check_Weapon,
            // at the end of the states above, a use item has been selected in the enemy's hand. here the enemy uses it, and if there are
            // two or more tokens left, the enemy repeats the cycle. they need one token to attack, so they won't be using that.

            Use_Item,
            Attack
        };

        EnemyModel1(){};
        ~EnemyModel1(){};

        State current_state;

    public:
        static EnemyModel1 instance()
        {
            static EnemyModel1 x;
            return x;
        }

        void set(HumanEnemy *reference_ptr)
        {
            self = reference_ptr;
        }

        void execute() //currently an even simpler test implementation. 
        {   
            bool attacked = false;
            while (true){
                switch (current_state)
                {
                case State::Entry:
                    if (self->hpFullPercent() < 25)
                    {
                        current_state = State::Dangerously_Low_HP;
                    }
                    else if (self->hpFullPercent() < 90)
                    {
                        current_state = State::Low_HP;
                    }
                    else
                    {
                        current_state = State::HpFine;
                    }
                    break;
                case State::Dangerously_Low_HP:
                    DLHP();
                    current_state = State::Entry;
                    //sorts healing items based on how close using them brings them closest to 90 percent of max health.
                case State::Low_HP:
                case State::HpFine:
                
                case State::Low_STA:
                    
                case State::Check_Weapon:
                case State::Use_Item:
                case State::Attack:
                    attack(player);
                    attacked = true;
                    break;
                }
                if (attacked) break;
            }
        };
        
        void DLHP(){
            vector<Item> inv = *(self->getInv());
            sort(inv.begin(), inv.end(), SortByV);
        }

        bool SortByV(ValuedComponent i1, ValuedComponent i2){
            return i1.getValue() > i2.getValue();
        }

        bool SortByUP(ValuedComponent i1, ValuedComponent i2){
            return i1.usePercent() > i2.usePercent();
        }
        
        //!stub implementations.
        void attack(Player* player){
            player->takedamage(self->getDMG());
        }
        int calculateDamage(Player* player, Weapon* weapon){
            return self->getDMG();
            //copy an entity with the relevant parameters and deal damage to them and see how much it does.
        }
    };

    class CombatController
        {
            // has a return result function. currently a stub is enough. maybe put it in the destructor?
            Entity *friendPTR;
            Entity *foePTR;

        public:
            static CombatController &GetInstance()
            {
                static CombatController combatInstance;
                return combatInstance;
            }

            static Entity *getFriendPTR() { return CombatController::GetInstance().imp_getFriendPTR(); }
            static Entity *getFoePTR() { return CombatController::GetInstance().imp_getFoePTR(); }

        private:
            Entity *imp_getFriendPTR() { return friendPTR; }
            Entity *imp_getFoePTR() { return foePTR; }

            void Imp_GameLoop()
            {
                // needs
                while (friendPTR->isAlive() && foePTR->isAlive())
                {
                    utils::slowPrint("this is a custom message. \n");
                    utils::slowPrint("What will you do? \n");
                    
                    // give initial message,
                    // ask what will you do?
                    // have the attack animation
                    //
                }
            }
            // void action(Entity* towho, pair <action, value>);
        };



}

// enemy combat fsm 2:
// this implementation is based on a version I found on the internet. The idea is that every state is a singleton
// instead of an enum. every state has a set of actions it calls upon an object entering that state, a set of actions
// it calls upon an object exiting the state, and a special toggle action, which makes it possible to incorporate
// other types of fsm systems, like the one above.
namespace combat2
{
    
}

// enemy combat fsm 3:
// this implementation uses a third party library. There are many things implemented, including events,
//
namespace combat3
{

}

// in this implementation, each enemy has multiple parameters that can be in different states.
namespace combat4
{

}
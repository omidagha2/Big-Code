#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <random>
#include <time.h>
#include <map>
using namespace std;

const int SP_CHAR_DELAY_DEFAULT = 60;
const int SP_PAR_DELAY_DEFAULT = 1500;
const bool NOCLS = false;

class DamageComponent;
class Entity;
class CombatController;
class Weapon;
class FireArm;
class Melee;
class HumanEnemy;
class Human;
class Player;
vector<string> nextPrompts = {};
bool relics[7] = {};
int globalluck = 0;
/*
0: makes melee vision horrible, maybe broken glasses.
1: increase luck by 2.
2: makes guns more accurate.
3: increases fire damage (makes everyone weak against it) and decreases freeze damage (makes everyone strong against it)
4: adds one to your tokens.
5: increases any weapon's max ammo by 1.
6: one that reduces luck but adds to your strength. for melee weapon build.
*/

vector<string> relicDescriptions{
    "Spectacles of Misfortune:\n These spectacles were once worn by a nearsighted barbarian who mistook a dragon for a damsel. Wearing them may turn your vision into a blurry mess, making every foe look fearsomely fuzzy.",
    "Lucky Rabbit's Foot:\n Not your ordinary foot—this one's from a rabbit that survived five encounters with a fox, two forest fires, and a tax audit. Although, if the rabbit was so lucky, it's foot wouldn't be here.\n Carrying it boosts your luck by 2. ",
    "Sharpshooter's Monocle:\n Believed to have belonged to the legendary sniper but found under an ordinary tree.\n This monocle sharpens your aim, making guns far more accurate. Just don’t look into the sun.",
    "Pyro's Mood Ring:\n Changes colors with your fiery outbursts and cools down with your chill vibes. It increases fire damage (setting even the moodiest monsters ablaze) and decreases freeze damage (because cold hearts can't hurt you).",
    "Bargaining Chicken:\n Trained by a famous chicken trainer to talk, This chick knows a very useful sentence she repeats each turn: \"Please, just one more day!\". And she fits in your pocket! \nAdding her to your arsenal gives you an extra move in your turn, because sometimes, all you need is one more roll to turn the tides.",
    "The Great Alchemist's Tape:\n Belonged to an eccentric alchemist who believed everything could hold \"just one more.\" Strap it on any weapon to increase it's max ammo by 1-although it's famous for it's other \"uses\"",
    "Boulder's Bracelet:\n Worn by a famous arm-wrestler who was terrible at gambling but great at brawling. This relic reduces your luck but grants the strength to arm-wrestle a bear—or at least swing a mean club (+1 damage)."};

//utility functions
namespace utils
{

    //has a one over (denom) chance to return true, scales with luck (has a chance of 1/(d-l*lm) to return true.)
    bool roll(int denom, int luck = 0, int luck_mult = 1)
    { 
        int a = denom - luck * luck_mult;
        return a <= 0 ? true : rand() % a == 0;
    }

    //currently unused
    enum Color
    {
        ORANGE,
        RED,
        GREEN,
        BLUE,
        WHITE

    };

    //returns the strings in the nextPrompts global vector<string> variable and clears it.
    vector<string> popNextPrompts()
    {
        vector<string> temp = nextPrompts;
        nextPrompts.clear();
        return temp;
    }

    //waits for a key press and returns it.
    char waitForInpt()
    {
        int i;
        while (true)
        {
            if ((kbhit()) && (i = getch()))
            {
                if (i != 0)
                    return i;
            };
        }
    }

    //slowlyy prints a bunch of strings. use @'s in your strings to skip char delay for chars in between, ~'s to skip whitespaces between sentences, ^'s to skip delay between sentences. use the backslash (\) button on keyboard to skip a sentence slowprinting.
    int slowPrintPrompts(vector<string> prompts, vector<int> input_vector = {}, char skip_key = '\\', double char_delay_ms = SP_CHAR_DELAY_DEFAULT, double sentence_delay_ms = SP_PAR_DELAY_DEFAULT, string sentence_sep = "\n", Color color = WHITE, int responsiveness = 20)
    {
        int p, chardel = char_delay_ms, sendel = sentence_delay_ms;
        if (find(input_vector.begin(), input_vector.end(), skip_key) != input_vector.end())
            cout << "warning: this prompt accepts the skip key as input. it's likely the skip key won't work this time. ";
        for (int i = 0; i < prompts.size(); i++)
        {
            for (char c : prompts[i])
            {
                if ((kbhit()) && (p = getch()))
                {
                    if (find(input_vector.begin(), input_vector.end(), p) != input_vector.end())
                        return p;
                    if (p == skip_key)
                    {
                        char_delay_ms = 0;
                        sentence_delay_ms = 0;
                    }
                };
                if (c == '@')
                {
                    if (char_delay_ms == chardel)
                    {
                        char_delay_ms = 0;
                        sentence_delay_ms = 0;
                    }
                    else
                    {
                        char_delay_ms = chardel;
                        sentence_delay_ms = sendel;
                    }
                }
                else if (c == '^')
                {
                    if (sentence_delay_ms == sendel)
                    {
                        sentence_delay_ms = 0;
                    }
                    else
                    {
                        sentence_delay_ms = sendel;
                    }
                }
                else if (c == '~')
                {
                    if (sentence_sep == "\n")
                        sentence_sep = "";
                    else
                        sentence_sep = "\n";
                }
                else
                    cout << c;
                Sleep(char_delay_ms);
            }
            if (i != prompts.size() - 1)
            {
                for (int j = 0; j < sentence_delay_ms / responsiveness; j++)
                {
                    Sleep(responsiveness);
                    if (kbhit() && (p = getch()))
                    {
                        if (find(input_vector.begin(), input_vector.end(), p) != input_vector.end())
                            return p;
                        if (p == skip_key)
                        {
                            char_delay_ms = 0;
                            sentence_delay_ms = 0;
                        }
                    }
                }
                cout << sentence_sep;
            }
        }
        sentence_delay_ms = sendel;
        char_delay_ms = chardel;
        if (input_vector.size() > 0)
        {
            while (true)
            {
                int input = waitForInpt();
                if (find(input_vector.begin(), input_vector.end(), input) == input_vector.end())
                {
                }
                else
                    return input;
            }
        }
    }

    // a simpler easy to call version of slowPrintPrompts for when there is just one sentence
    void slowPrint(string prompt, Color color = WHITE, double char_delay_ms = SP_CHAR_DELAY_DEFAULT)
    {
        slowPrintPrompts({prompt});
    }

    //clears screen
    void cls()
    {
        if (NOCLS)
            return;
        system("cls");
    }

    //clears a line (iunimplemented)
    void cll()
    {
    }

    //suitable for making menus. Slowly prints prepromt, then the choices, then for each choice a description below. you can move freely between choices
    int promptUser(vector<string> choices, vector<string> preprompt, vector<vector<string>> choice_descriptions = {}, int choicemargin = 0)
    {
        if (choices.size() < choicemargin){
            for (int i = 0; i < choicemargin - choices.size(); i++)choices.push_back(".");
        }
        while (choice_descriptions.size() < choices.size()) choice_descriptions.push_back({{}});
        slowPrintPrompts(preprompt);
        Sleep(500);
        cout << endl;

        int choice = 0;
        while (true)
        {
            cls();
            slowPrintPrompts(preprompt, {}, '\\', 0, 0);
            int max_choice_length = 10;
            cout << endl;
            for (int i = 0; i < choices.size(); i++)
            {
                if (choices[i].length() > max_choice_length)
                    max_choice_length = choices[i].length();
            }
            for (int i = 0; i < max_choice_length; i++)
                cout << '~';
            cout << endl;
            for (int i = 0; i < choices.size(); i++)
            {
                if (i == choice)
                    cout << '>';
                cout << i + 1 << ". " << choices[i] << endl;
            }
            for (int i = 0; i < max_choice_length * 1.2; i++)
                cout << '~';
            cout << endl;
            vector<string> desc;
            // if (choice_descriptions.size() == 1){
            //     //won't skip current prompt
            // }
            if (choice >= choice_descriptions.size())
                desc = {""};
            else
                desc = choice_descriptions[choice];
            int ud = slowPrintPrompts(desc, {72, 80, 13});
            if (ud == 72)
            {
                choice = max(choice - 1, 0);
            }
            else if (ud == 80)
            {
                choice = min(choice + 1, int(choices.size()) - 1);
            }
            else if (ud == 13)
            {
                return choice + 1;
            }
        }
    }
}


class Item
{
protected:
    Human *owner;
    string name;
    vector<string> description;
    int token_uses;

public:
    virtual void putInInv(Human *human);
    virtual void removeFromInv(Human *human);

    int getTokenUse() { return token_uses; }
    vector<string> getDesc();
    void setDesc(vector<string> desc);
    Item(string argName, vector<string> desc, Human *argOwner = nullptr, int tu = 1)
    {
        name = argName;
        owner = argOwner;
        description = desc;
        token_uses = tu;
    }
    string getname() { return name; };
    virtual string getType();
    void setName(string argName);
    void setOwner(Human *);
};

class Weapon : public Item
{
protected:
    //holds a bunch of DamageComponents allowing for mixed types of damage.
    vector<DamageComponent> dcvector;

public:
    string getDamageDesc();

    //returns a string showing stats for the weapon.  it's meant to be overwritten later.
    virtual string getinfo(){};

    //tries to return how much damage an entity would take if it were to be attacked by this weapon
    virtual int estimateDamage(Entity *entity);
    virtual vector<DamageComponent> getDcVector();
    Weapon(string argName, vector<DamageComponent> dcs, vector<string> desc = {}, Human *argOwner = nullptr, int tu = 1);

    virtual string getType();
};

//an object to refill ammo on a gun (currently unused in the game)
class AmmoBox : public Item
{
public:
    void apply(FireArm *);
};

class FireArm : public Weapon
{
    int max_ammo;
    int ammo;

public:
    int getAmmo() { return ammo; }
    int getMaxAmmo() { return max_ammo; }
    //refills ammo a certain amount, or fully if no arguments are given.
    int refillAmmo(int amount = -1) { ammo = (amount == -1 ? max_ammo : min(max_ammo, ammo + amount)); }
    //decrease ammo a certain amount.
    int decreaseAmmo(int amount = 1) { ammo = max(ammo - amount, 0); }
    FireArm(string argName, vector<DamageComponent> dcs, vector<string> desc, int ARGmax_ammo, int ARG_ammo, Human *argOwner = nullptr, int tu = 1);
    
    //overriden get info function that displays damage, ammo, max ammo and token usage.
    string getinfo() override
    {
        string str = ("[Damage: ");
        str += getDamageDesc() + " - Ammo: " + to_string(getAmmo()) + "/" + to_string(getMaxAmmo()) + " - Tokens: " + to_string(getTokenUse()) + "]";
        return str;
    }
};

class Melee : public Weapon
{
    //// modifiers here?
public:
    Melee(string argName, vector<DamageComponent> dcs, vector<string> desc = {}, Human *argOwner = nullptr, int tu = 1)
        : Weapon(argName, dcs, desc, argOwner, tu){};

    //overriden getinfo functoin that shows (returns a string of) damage and tokens
    string getinfo() override
    {
        string str = ("[Damage: ");
        str += getDamageDesc() + " - Tokens: " + to_string(getTokenUse()) + "]";
        return str;
    }
};

//a class for any kind of component that has a value aspect and needs to know how full that value is (changed premises a bit)
class ValuedComponent
{
protected:
    int max_value;

public:
    virtual string getType();
    virtual int getMaxVal();
};

//implemented valuedcomponents
struct Stat
{
    class HealthComponent : public ValuedComponent
    {
    public:
        HealthComponent(int v);
        string getType() override;
    };

    class StaminaComponent : public ValuedComponent
    {
    public:
        StaminaComponent(int v);
        string getType() override;
    };
};


class Consumable : public Item
{
    vector<ValuedComponent *> valueComponents;
    vector<DamageComponent> damageComponents;

public:
    Consumable(string name, vector<ValuedComponent *> VCs, vector<DamageComponent> DCs = {}, vector<string> desc = {}, Human *owner = nullptr, int tokenUses = 1);
    string getType();
    vector<ValuedComponent *> &getValueComponents();
    void addVC(ValuedComponent *vc);

    //returns how much it would heal
    int getTotalHealAmount();

    // applies the consumable onto an entity. heals them for it's healing components and famages them for it's damaging components. Doesn't remove the consumable object.
    void apply(Entity *entity);

    //function to make evaluation for fsm easier
    int getBenefit(bool valuematters = true, bool damagematters = true);
};

//a class for any collection of items.
class ItemBunch
{
    vector<Item *> items;

public:
    ItemBunch(vector<Item *> argitems = {})
    {
        items = argitems;
    }

    void addItem(Item *item)
    {
        items.push_back(item);
    }

    void removeItem(Item *item)
    {
        if (find(items.begin(), items.end(), item) != items.end())
            items.erase(find(items.begin(), items.end(), item));
    }
    ~ItemBunch()
    {
        for (Item *item : items)
        {
            delete item;
        }
    }

    // prompts the player and returns the item chosen. 
    Item *displayAndChooseItem()
    {
        if (items.empty())
        {
            cout << "No items available." << endl;
            return nullptr;
        }

        vector<string> itemNames;
        vector<vector<string>> itemDescriptions;

        for (const auto &item : items)
        {
            itemNames.push_back(item->getname());
            itemDescriptions.push_back(item->getDesc());
        }

        vector<string> preprompt = {"Please choose an item: "};
        int choice = utils::promptUser(itemNames, preprompt, itemDescriptions, 5);
        return items[choice - 1];
    }

    vector<Item *> getVector()
    {
        return items;
    }
};

class Entity
{
protected:
    string name;
    int age;
    string weaknesses; // a string that represents weakness array. ice being in the stirng means the entity is weak against ice, etc.
    string withstands; // same thing as weaknesses stirng
    string gender;
    vector<double> mults;
    int lvl;
    int hp;
    int max_hp;
    int dmg;
    int luck;
    vector<string> prompts;
    bool onfire;
    bool frozen;

public:
    virtual bool isAlive();

    //these two are the same, but i've used different versions in different places and an afraid to remove one
    void heal(int amount);
    int healAmount(int amount);

    virtual string getname() { return name; }

    //returns an int between 0 and 100.
    virtual int hpFullPercent();

    //returns how much damage would be dealt by a damage component, takes a multiplier or a list (vector of size 5) of them for each damage type.
    virtual int calculateDmg(DamageComponent, double = 1, vector<double> mults = {});

    //deals damage to an entity. (unused currently)
    virtual void dealDamage(int amount, Entity *entity);

    //applies a cvaluedomponent onto the entity.
    virtual void consumeComponent(ValuedComponent *vc);

    //applies a damage component to the entity. 
    virtual void consumeDC(DamageComponent dc);

    //returns how much damage would be taken by a weapon, which is the sum of all damages from the damage components. takes weaknesses and withstands into account. 
    virtual int calculateDmgWpn(Weapon *weapon, double mult = 1, vector<double> mults = {});

    //gets attacked by a weapon
    virtual int getAttacked(Weapon *weapon, double multiplier = 1);

    //currently unused die function
    virtual void die();
    virtual void addweakness(string str) { weaknesses.append(str); }
    virtual void addwithstand(string str) { withstands.append(str); }
    vector<double> getmults() { return mults; }
    void setonfire() { onfire = true; }
    void freeze() { frozen = true; }

    //sets freezing and onfire fields false if both are true.
    void freezeNFire()
    {
        if (onfire && frozen)
        {
            nextPrompts.push_back("Fire and ice cancel each other out! " + getname() + " is neither frozen nor burning! ");
            onfire = false;
            frozen = false;
        }
    }

    //returns a string containing info on level, hpp, damage.
    string getinfo()
    {
        return ("[LVL: " + to_string(lvl) + " - HP: " + to_string(hp) + " - DMG: " + to_string(dmg) + "]");
    }
    bool isfrozen() { return frozen; }
    bool isBurning() { return onfire; }

    //randomly returns a prompt from the entity's prompts
    string getRandomPrompt()
    {
        if (prompts.empty())
            return "This one's got nothing to say";
        return prompts[rand() % prompts.size()];
    }

    Entity();
    Entity(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, string withstandstr = "", string weaknessstr = "", vector<string> argPrompts = {}, vector<double> argmults = {})
        : name(argName), age(argAge), gender(argGender), lvl(argLVL), hp(argHP), max_hp(argHP), dmg(argDMG), prompts(argPrompts), mults(argmults) {}
    virtual string getType();
    int getHp();
    int getHpMax();
    int getLVL();
    int getDMG();

    //simple function for when you just need to take some int damage
    void takeIntDamage(int);
    void setluck(int l) { luck = l; }
    int getluck() { return luck; }
};


class Human : virtual public Entity
{
protected:

    //getname() function wouldn't work so i make a backup name because i don't understand virtual inheritence
    string bname;
    Weapon *melee_weapon;
    Weapon *firearm_weapon;
    vector<Item *> inventory;
    int max_combat_tokens;
    int combat_tokens;

public:

    //calls entity's take damage from weapon function
    virtual void attackWith(Weapon *weapon, Entity *entity);

    //consumes a consumable, calls delete on the consumable pointer
    virtual void useConsumable(Consumable *);

    //adds an item to the inventory. also makes the item's owner this entity.
    virtual void takeInInv(Item *item);

    //consumes an item if it's a consumable
    virtual void consumeConsumable(Item *consumable);

    //removes an item from the inventory and calls delete on it.
    virtual void removeFromInv(Item *item);
    virtual void addCombatTokens(int amount)
    {
        combat_tokens = min(amount + combat_tokens, max_combat_tokens);
    }

    //returns how much value of the valued component would actually be used
    int effectiveValue(ValuedComponent *vcptr);
    vector<string> getItemNames();
    Human(){};

    Human(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, vector<Item *> argInv = {}, vector<string> argPrompts = {}, string withstandstr = "", string weaknessstr = "", vector<double> argmults = {});
    virtual string getType();
    vector<Item *> getInv();

    //returns a vector of all the consumables in the inventory (which is the only type of thing that can be in there currently, so this is also useless)
    vector<Consumable *> getConsumablesInv();


    int getCombatTokens() { return combat_tokens; }
    int getMaxCombatTokens() { return max_combat_tokens; }
    void increaseMaxCombatTokens(int amount) { max_combat_tokens += amount; }
    void setCombatTokens(int amount) { combat_tokens = min(max_combat_tokens, amount); }

    //a fancier name for decrease tokens
    void usetokens(int amount) { setCombatTokens(max(0, combat_tokens - amount)); }
    
    void setfirearm(Weapon *fa);
    Weapon *getFireArm();
    void setMelee(Weapon *fa);
    Weapon *getMelee();
    virtual string getname() override
    {
        return name;
    }
};

class Player : public Human
{
    vector<Item *> special_items_inventory; // won't fill up (has no cap).
    int balance;//unused as I forgot about it

public:

    //takes in amount. returns true and decreases balance if it can afford that amount, otherwise returns false.
    bool tryPurchase(int amount)
    {
        if (amount > balance)
        {
            return false;
        }
        else
        {
            balance -= amount;
            return true;
        }
    }
    Player(){};

    //returns true if there's a peanut butter in the inventory
    bool haspbs();

    void setInv(vector<Item*> inv){
        inventory = inv;
    }

    //prompts the user with an attack interface, returns an integer based on how good they did. you can change the crosshair,
    // make it so it doesn't show the picture with the characters, or make it so it returns score based on how far it went only.
    // you can probably change the length of the graphical interface too but that might be bugged.
    int atkBarGun(int offset, int length = 11, bool rawscore = false, bool showting = true, char crosshair = '^');

    //similar thing as atkbargun (infact calls it) but tailored for a melee weapon interface
    int atkBarMelee(int offset);

    //unused
    int CombatMenuPrompt(vector<string>);
    //unused
    void inventoryPrompt(); // throwable, consumable, ammo_box, needle, ...
    //unused
    void meleePrompt();
    //unused
    void specialItemsPrompt();
    //unused
    void shootPrompt();
    //unused
    void attackWithMelee(Weapon *weapon, Entity *entity);
    //unused
    void attackWithGun(Weapon *weapon, Entity *entity);


    void addSpecialItem(Item *item);
    vector<Item *> getSpecialItems();
    void removeSpecialItem(Item *);

    //updates the variables and functionalities associated with having certain relics unlocked (currently only tokens are implemented)
    void updateRelics();

    //clears nextPrompts global variable
    void resetNextPrompts() { nextPrompts = {}; }
    void addtoNextPrompts(string np) { nextPrompts.push_back(np); }
    void setlvl(int i) { lvl = i; }
    vector<string> getNextPrompts() { return nextPrompts; }

    virtual ~Player(){};                                                                                                                                                                    //there's still so much more story i want to implement
    string getname() override
    {
        return bname;
    }
    Player(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, vector<Item *> argInv = {}, string withstr = "", string weakstr = "");
    virtual string getType();
};

//unused
class Shop
{
    ItemBunch itemsinstock;

public:
};

class Enemy : virtual public Entity
{
protected:
    string bname; //same thing as before

public:
    Enemy(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, string withstr, string weakstr, vector<string> argPrompts = {}, vector<double> argmults = {})
        : Entity(argName, argAge, argGender, argLVL, argHP, argDMG, withstr, weakstr, argPrompts, argmults) { bname = argName; }
    Enemy(){};

    virtual string getType() override;
    virtual string getname() override
    {
        return bname;
    }
};

//a class for all things that can be simplified to a damage amount and a amage type
class DamageComponent
{
public:
    enum class TYPE
    {
        regular = 0,
        ice,
        fire,
        explosion,
        peanut_butter
    };

private:
    TYPE dmgType;
    int damage;

public:
    //returns how much damage an entity would take, taking into account weaknesses and withstands. 
    virtual int simulateDamage(Entity *entity);

    //returns the string version of dmgType
    string getTypeStr();

    //returns an int version of dmgType representing one of the (currently 5) implemented
    int getTypeInt()
    {
        return int(dmgType);
    }
    int getDmg();
    DamageComponent(int dmg, TYPE type = TYPE::regular);
    DamageComponent(){};
};

class Zombie : public Enemy
{
    string cname;//bname wouldn't work, soo i mad another don't judge pls it works
    DamageComponent dmgcmp;

public:
    Zombie(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, string withstr, string weakstr, vector<string> argPrompts = {}, vector<double> argmults = {})
        : Enemy(argName, argAge, argGender, argLVL, argHP, argDMG, withstr, weakstr, argPrompts, argmults) { cname = argName; }

    void zombieAttack(Player *player);
    string getname()
    {
        return cname;
    }
};

// #a punch melee weapon?

class HumanEnemy : public Human, public Enemy
{
    friend class Combat;

    //states for the fsm logic to move through
    enum State
    {
        CalcBestWeapon,
        Entry,
        DangerouslyLowHp,
        KindaLowHp,
        HpFine,
        AreThereTokens,
        Attack
    };
    vector<string> state_prompts; //holds prompts for each state
    State current_state;
    string dialogue;
    string cname; //yup
    Player *target;

    //holds best weapon calculated at the CalcBestWepaon state
    Weapon *bw;

    //holds the amount of tokens to reserve for the bw calculated at the CalcBestWeapon state
    int tokens_after_best_weapon;

    //holds the best consumable calculated at one of the second states
    Consumable *bestConsumable;

public:
    void setCurrentState(State state) { current_state = state; }
    State getCurrentState() { return current_state; }

    //return a string versoin of current state
    string getStateStr()
    {
        switch (current_state)
        {
        case 0:
            return "CalculateBestWeapon";
        case 1:
            return "Entry";
        case 2:
            return "DangerouslyLowHp";
        case 3:
            return "KindaLowHp";
        case 4:
            return "HpIsFine";
        case 5:
            return "AreThereTokens";
        case 6:
            return "Attack";
        }
    }

    //returns a description based on the current state
    string getStateDesc()
    {
        switch (current_state)
        {
        case 0:
            return "Calculate the best weapon based on it's damage/token ratio, and reserves tokens for it. ";
        case 1:
            return "Determine what it should do next based on how much hp it has. ";
        case 2:
            return "Not care about reserving tokens and uses the best healing item it has. ";
        case 3:
            return "Use a healing item with the best value that will also leave enough tokens for the attack. ";
        case 4:
            return "Use a throwable or a damage inducing consumable with the best value that also leaves enough tokens for the attack. ";
        case 5:
            return "Determine what to do next based on how many extra tokens they have. ";
        case 6:
            return "Attacks and ends turn. ";
        }
    }


    vector<string> getStatePrompts() { return state_prompts; }
    void setStatePrompts(vector<string> spv) { state_prompts = spv; }

    //returns how much of the caluedcomponent would be effectively used in percents
    int usePercentVC(ValuedComponent *vcptr);

    //returns how much of the consumable would be effectively used in percents
    int usePercentConsumable(Consumable *cons);

    Weapon *getbw();

    //tries to find the best weapon for a speific target
    Weapon *findBestWeapon(Entity *target);

    HumanEnemy(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, vector<Item *> argInv = {}, vector<string> randomprompts = {}, vector<string> stateprs = {}, string withstr = "", string weakstr = "", vector<double> argmults = {});
    virtual string getType() override;
    int gettabw() { return tokens_after_best_weapon; }
    void settabw(int amount) { tokens_after_best_weapon = amount; }

    //called from a second state to find the most suitable consumable. can be in 3 modes: 
    //1 means valued components matter only, 2 means the same but with damagecomponents, 3 means they both matter.
    Consumable *findBestConsumableForUtilization(int mode);

    //called at the calculatebestweapon state
    Weapon *calculateBestWeapon(Player *target);
    int hpFullPercent();
    string getname() override { return cname; }
};

void Entity::consumeDC(DamageComponent dc)
{
    takeIntDamage(calculateDmg(dc, 1, mults));
    nextPrompts.push_back(getname() + " took " + to_string(calculateDmg(dc, 1, mults)) + " " + dc.getTypeStr() + " damage and is now on " + to_string(getHp()) + " health.");
}

Consumable *HumanEnemy::findBestConsumableForUtilization(int mode)
{ // 0: healing value, 1: least wasteful healing, 2: highest damage
    int i, j;
    switch (mode)
    {
    case 1:
        i = 1, j = 0;
        break;
    case 2:
        i = 1, j = 0;
        break;
    case 3:
        i = 0;
        j = 1;
        break;
    }
    Consumable *bestConsumable = nullptr;
    double bestBenefitRatio = 0;

    for (Item *item : inventory)
    {
        Consumable *consumable = dynamic_cast<Consumable *>(item);
        if (consumable)
        {
            int totalBenefit = consumable->getBenefit(i, j);
            int cost = consumable->getTokenUse();
            double benefitRatio = cost > 0 ? double(totalBenefit) / cost : 0;

            if (cost <= combat_tokens - tokens_after_best_weapon && benefitRatio > bestBenefitRatio)
            {
                bestBenefitRatio = benefitRatio;
                bestConsumable = consumable;
            }
        }
    }
    return bestConsumable;
}

int Player::atkBarGun(int offset, int length, bool rawscore, bool showthing, char crosshair)
{
    int score = 1;
    string backspc = "\b \b\b";
    backspc.push_back(crosshair);
    string forward = "\b ";
    forward.push_back(crosshair);
    length = max(length, 11);
    int way = 1;
    if (showthing)
    {
        cout << endl;
        for (int i = 0; i < (length - 7) / 2; i++)
        {
            cout << '~';
        }
        cout << char(176) << char(177) << char(177) << char(178) << char(177) << char(177) << char(176);
        for (int i = 0; i < (length - 7) / 2; i++)
        {
            cout << '~';
        }
        cout << endl;
    }
    /*  ░▒▒▓▒▒░  */
    while (true)
    {
        for (int i = 0; i < 8; i++)
        {
            Sleep(10);
            if (kbhit() && getch() == ' ')
            {
                int n = ceil(length / 2.0);
                return (rawscore ? score : max(0, n - abs(n - score)));
            }
        }
        if (score == length)
        {
            way = -1;
        }
        else if (score == 1)
        {
            way = 1;
        }
        score += way;
        cout << (way < 0 ? backspc : forward);
    }
}

Weapon *HumanEnemy::getbw()
{
    return bw;
};

int Player::atkBarMelee(int offset)
{
    int score = 0;
    int way = 1;
    if (!relics[0])
        cout << endl
             << "~~~~" << char(176) << char(176) << char(176) << char(177) << char(177) << char(177) << char(178) << endl;
    else
        cout << endl
             << '.' << ',' << '-' << char(169) << '~' << char(174) << char(22) << char(31) << char(254) << char(219) << char(178) << endl;
    return atkBarGun(offset, 11, true, false, '*');
}
DamageComponent::DamageComponent(int dmg, TYPE type)
{
    damage = dmg;
    dmgType = type;
};

int HumanEnemy::hpFullPercent()
{
    return hp * 100 / max_hp;
};

Consumable::Consumable(string name, vector<ValuedComponent *> VCs, vector<DamageComponent> DCs, vector<string> desc, Human *owner, int tokenUses)
    : Item(name, desc, owner, tokenUses), valueComponents(VCs), damageComponents(DCs) {}

void Player::updateRelics()
{
    // based on special items available, change global variables. maybe just for the player. or maybe it's a singleton. idk.
    max_combat_tokens = 3 + relics[4];
}

void Item::removeFromInv(Human *human)
{
    human->removeFromInv(this);
    delete this;
}

void Player::addSpecialItem(Item *item)
{
    special_items_inventory.push_back(item);
    item->setOwner(this);
}

void Player::removeSpecialItem(Item *item)
{
    special_items_inventory.erase(find(special_items_inventory.begin(), special_items_inventory.end(), item));
    delete item;
}

void Item::setOwner(Human *human)
{
    owner = human;
}

bool Player::haspbs(){
    for (Item* i: inventory){
        if (i->getname() == "Peanut Butter Sandwich"){
            return true;
        }
    }
    return false;
};

Weapon *HumanEnemy::calculateBestWeapon(Player *target)
{
    bw = nullptr;
    double bestRatio = 0;

    // for (Item *item : inventory) //#old implementation, for when weapons would be in inventory.
    vector<Item *> items = {getMelee(), getFireArm()};
    for (Item *item : items)
    {
        Weapon *weapon = dynamic_cast<Weapon *>(item);
        if (weapon)
        {
            int damage = weapon->estimateDamage(target);
            int cost = weapon->getTokenUse();
            double ratio = (cost > 0 ? (double(damage)) / cost : 0);

            if (ratio > bestRatio)
            {
                bestRatio = ratio;
                bw = weapon;
                tokens_after_best_weapon = combat_tokens - cost;
            }
        }
    }

    if (bw)
    {
        nextPrompts.push_back("selected best weapon: " + bw->getname() + " with damage-to-token ratio: " + to_string(bestRatio));
    }
    else
    {
        nextPrompts.push_back("No suitable weapon found.");
    }
};

Weapon *HumanEnemy::findBestWeapon(Entity *target)
{
    Weapon *bestWeapon = nullptr;
    double bestRatio = 0.0;
    for (Item *item : inventory)
    {
        Weapon *weapon = dynamic_cast<Weapon *>(item);
        if (weapon)
        {
            int damage = weapon->estimateDamage(target);
            int tokenCost = weapon->getTokenUse();
            double ratio = tokenCost > 0 ? static_cast<double>(damage) / tokenCost : 0;
            if (ratio > bestRatio)
            {
                bestRatio = ratio;
                bestWeapon = weapon;
            }
        }
    }
    return bestWeapon;
}

vector<Item *> Player::getSpecialItems()
{
    return special_items_inventory;
}

int Consumable::getTotalHealAmount()
{
    int totalHeal = 0;
    for (auto vc : valueComponents)
    {
        if (auto hc = dynamic_cast<Stat::HealthComponent *>(vc))
        {
            totalHeal += hc->getMaxVal();
        }
    }
    return totalHeal;
}

void Entity::die(){}; //!
void Human::attackWith(Weapon *weapon, Entity *entity)
{
    entity->getAttacked(weapon);
}; //!

vector<string> Human::getItemNames()
{
    vector<string> names = {};
    for (Item *i : inventory)
    {
        names.push_back(i->getname());
    }
    return names;
}

void AmmoBox::apply(FireArm *weapon)
{
    weapon->refillAmmo();
    nextPrompts.push_back(owner->getname() + " refilled " + weapon->getname() + ". The gun now has " + to_string(weapon->getAmmo()) + " shots left.");
    owner->removeFromInv(this);
    delete this;
}

FireArm::FireArm(string argName, vector<DamageComponent> dcs, vector<string> desc, int ARGmax_ammo, int ARG_ammo, Human *argOwner, int tu)
    : Weapon(argName, dcs, desc, argOwner)
{
    max_ammo = ARGmax_ammo;
    ammo = ARG_ammo == -1 ? ARGmax_ammo : ARG_ammo;
};

string Weapon::getDamageDesc()
{
    string str = "";
    for (auto dc : dcvector)
    {
        str += to_string(dc.getDmg()) + " " + dc.getTypeStr() + ", ";
    }
    str += "\b\b  ";
    return str;
}
vector<string> Item::getDesc()
{
    return description;
}

void Item::setDesc(vector<string> desc)
{
    description = desc;
}

int Consumable::getBenefit(bool valuematters, bool damagematters)
{
    int sum = 0;
    for (auto vc : valueComponents)
    {
        sum += vc->getMaxVal() * valuematters;
    }
    for (auto dc : damageComponents)
    {
        sum += dc.getDmg() * damagematters;
    }
    return sum;
};

void Player::attackWithGun(Weapon *weapon, Entity *entity)
{
    entity->getAttacked(weapon);
    auto gunptr = dynamic_cast<FireArm *>(weapon);
    if (gunptr == nullptr)
        utils::slowPrint(weapon->getname() + " is not a gun!\n");
    else
    {
        entity->getAttacked(weapon);
    }
};

void Player::attackWithMelee(Weapon *weapon, Entity *entity)
{
    entity->getAttacked(weapon);
    entity->takeIntDamage(dmg);
    //// nextPrompts.push_back("You dealt " + to_string(entity->calculateDmgWpn(weapon)) + " points of damage to " + entity->getname() + ". " + entity->getname() + " is now on " + to_string(entity->getHp()) + " hp.");
}
// maybe switch out the void stuff with stirngs that return the prompts for the attack. or don't

int DamageComponent::getDmg()
{
    return damage;
}

vector<DamageComponent> Weapon::getDcVector()
{
    return dcvector;
}

int Entity::getAttacked(Weapon *weapon, double multiplier)
{
    hp = max(0, hp - calculateDmgWpn(weapon, multiplier));
    string isorare = (name == "You" ? "are" : "is");
    nextPrompts.push_back(this->getname() + " got attacked for " + to_string(calculateDmgWpn(weapon, multiplier)) + " hp points and " + isorare + " now " + (isAlive() ? "on " + to_string(getHp()) + " hp." : "dead!"));
    return !isAlive();
}

int Entity::calculateDmgWpn(Weapon *weapon, double mult, vector<double> mults)
{
    int sum = 0;
    for (auto dc : weapon->getDcVector())
    {
        sum += calculateDmg(dc, mult);
    }
    return sum;
}

void Zombie::zombieAttack(Player *player)
{
    player->takeIntDamage(dmg);
}

int Weapon::estimateDamage(Entity *entity)
{
    int sum = 0;
    for (auto dc : dcvector)
    {
        sum += entity->calculateDmg(dc);
    }
    return sum;
};

string DamageComponent::getTypeStr()
{
    switch (dmgType)
    {
    case TYPE::regular:
        return "regular";
    case TYPE::ice:
        return "ice";
    case TYPE::fire:
        return "fire";
    case TYPE::explosion:
        return "explosion";
    case TYPE::peanut_butter:
        return "peanut";
    }
}

int Player::CombatMenuPrompt(vector<string> combatPrompt)
{
    int choice = utils::promptUser({"use a gun", "use a melee weapon", "look for useful combat items", "look in your schoolbag's second zipper"}, combatPrompt);
    switch (choice)
    {
    case 1:
        this->shootPrompt();
        break;
    case 2:
        this->meleePrompt();
        break;
    case 3:
        this->inventoryPrompt();
        break;
    case 4:
        this->specialItemsPrompt();
        break;
    }
};
// tbitbitbi
void Player::inventoryPrompt(){};
void Player::meleePrompt(){};
void Player::shootPrompt(){};
void Player::specialItemsPrompt()
{
}
void Entity::dealDamage(int amount, Entity *entity)
{
    entity->takeIntDamage(amount);
}
void Entity::takeIntDamage(int amount)
{
    hp = max(hp - amount, 0);
}

void Human::removeFromInv(Item *item)
{
    // remove pointer from inv, call delete for item.
    auto ptr = find(inventory.begin(), inventory.end(), item);
    if (ptr == inventory.end())
    {
        cout << "tried to remove an item from inventory that doesn't exist" << endl;
    }
    else
    {
        inventory.erase(ptr);
        delete item;
    }
}

void Human::setfirearm(Weapon *fa)
{
    firearm_weapon = fa;
}
Weapon *Human::getFireArm() { return firearm_weapon; }
void Human::setMelee(Weapon *mw)
{
    melee_weapon = mw;
}
Weapon *Human::getMelee()
{
    return melee_weapon;
}

void Human::consumeConsumable(Item *consumable)
{
    if (consumable->getType() != "Consumable")
    {
        cout << "consume function given a non consumable item\n";
        return;
    }
    if (find(inventory.begin(), inventory.end(), consumable) == inventory.end())
    {
        cout << "no such item\n";
        return;
    }
    Consumable *consptr = dynamic_cast<Consumable *>(consumable);
    string isorare = (getname() == "You" ? "are" : "is");
    nextPrompts.push_back(getname() + "  " + consptr->getname() + " and " + (isorare) + " now on " + to_string(getHp()) + " Hp with " + to_string(getCombatTokens()) + " move(s) left.");
    consptr->apply(this);
    inventory.erase(find(inventory.begin(), inventory.end(), consumable));
}
void Item::putInInv(Human *human)
{
    owner = human;
    human->takeInInv(this);
}

void Human::useConsumable(Consumable *item)
{
    item->apply(this);
    this->removeFromInv(item);
};
void Human::takeInInv(Item *item)
{
    if (inventory.size() > 5)
    {
        nextPrompts.push_back("Your inventory is full.");
        return;
    }
    inventory.push_back(item);
    //: what happens when you buy it from the shop/get it from loop:
    //: item's put in inventory function gets called, which in turn calls the human's take in inventory function. at the end of all that the item knows who owns it and the human knows that it's in their inventory.
}

void Item::setName(string argName) { name = argName; }

string Item::getType()
{
    return "Item";
}

Weapon::Weapon(string argName, vector<DamageComponent> argMod, vector<string> desc, Human *argOwner, int tu)
    : Item(argName, desc, argOwner), dcvector(argMod)
{
    owner = argOwner;
    description = desc;
};

string Weapon::getType()
{
    return "Weapon";
}

string ValuedComponent::getType()
{
    return "ValuedComponent";
}

int ValuedComponent::getMaxVal()
{
    return max_value;
}

Stat::HealthComponent::HealthComponent(int v)
{
    max_value = v;
}

string Stat::HealthComponent::getType()
{
    return "HealthComponent";
}

Stat::StaminaComponent::StaminaComponent(int v)
{
    max_value = v;
}

string Stat::StaminaComponent::getType()
{
    return "StaminaComponent";
}

void Consumable::addVC(ValuedComponent *vc)
{
    valueComponents.push_back(vc);
}

string Consumable::getType()
{
    return "Consumable";
}

vector<ValuedComponent *> &Consumable::getValueComponents()
{
    return valueComponents;
}

void Consumable::apply(Entity *entity)
{
    for (ValuedComponent *v : valueComponents)
    {
        entity->consumeComponent(v);
    }
    for (DamageComponent dc : damageComponents)
    {
        entity->takeIntDamage(entity->calculateDmg(dc, 1.0, entity->getmults()));
    }
}

Entity::Entity() : name(""), age(0), gender(""), lvl(1), hp(100), max_hp(100), dmg(10) {}

string Entity::getType()
{
    return "Entity";
}

bool Entity::isAlive()
{
    return hp > 0;
}

int Entity::getHp()
{
    return hp;
}

int Entity::getHpMax()
{
    return max_hp;
}

int Entity::getLVL()
{
    return lvl;
}

int Entity::getDMG()
{
    return dmg;
}

int Entity::healAmount(int amount)
{
    return min(hp + amount, max_hp) - hp;
}

void Entity::heal(int amount)
{
    hp = min(max_hp, hp + amount);
}

int Entity::calculateDmg(DamageComponent dmgcmp, double mult, vector<double> multsvec)
{ // should take damage component in actually
    if (multsvec.size() != 5)
    {

        if (weaknesses.find(dmgcmp.getTypeStr()) != string::npos)
        {
            return 1.5 * dmgcmp.getDmg() * mult;
        }
        else if (withstands.find(dmgcmp.getTypeStr()) != string::npos)
        {
            return 0.75 * dmgcmp.getDmg() * mult;
        }
        else
            return dmgcmp.getDmg() * mult;
    }
    else
    {
        return multsvec[dmgcmp.getTypeInt()] * dmgcmp.getDmg() * mult;
    }
}

int Entity::hpFullPercent()
{
    if (max_hp < 1)
        return -1;
    return (hp * 100) / max_hp;
}

void Entity::consumeComponent(ValuedComponent *vc)
{
    string type = vc->getType();
    if (type == "HealthComponent")
    {
        this->heal(vc->getMaxVal());
    }
    else if (type == "StaminaComponent")
    {
        if (auto a = dynamic_cast<Human *>(this))
        {
            a->addCombatTokens(vc->getMaxVal());
        }
    }
}

Human::Human(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, vector<Item *> argInv, vector<string> argPrompts, string withstandstr, string weaknessstr, vector<double> argmults)
    : Entity(argName, argAge, argGender, argLVL, argHP, argDMG, withstandstr, weaknessstr, argPrompts, argmults), inventory(argInv) { bname = argName; }

string Human::getType()
{
    return "Human";
}

vector<Item *> Human::getInv()
{
    return inventory;
}

vector<Consumable *> Human::getConsumablesInv()
{
    vector<Consumable *> csvector;
    for (Item *iptr : inventory)
    {
        if (iptr->getType() == "Consumable")
        {
            Consumable *cp = dynamic_cast<Consumable *>(iptr);
            csvector.push_back(cp);
        }
    }
    return csvector;
}

Player::Player(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, vector<Item *> argInv, string withstr, string weakstr)
    : Human(argName, argAge, argGender, argLVL, argHP, argDMG, argInv, {}, withstr, weakstr)
{
    inventory = argInv;
    bname = argName;
    hp = argHP;
}

string Player::getType()
{
    return "Player";
}

string Enemy::getType()
{
    return "Enemy";
}

HumanEnemy::HumanEnemy(string argName, int argAge, string argGender, int argLVL, int argHP, int argDMG, vector<Item *> argInv, vector<string> randomprompts, vector<string> stateprs, string withstr, string weakstr, vector<double> argmults)
    : Human(argName, argAge, argGender, argLVL, argHP, argDMG, argInv, randomprompts, withstr, weakstr, argmults)
{
    state_prompts = stateprs;
    cname = argName;
}

string HumanEnemy::getType()
{
    return "HumanEnemy";
}

int HumanEnemy::usePercentVC(ValuedComponent *vcptr)
{
    return effectiveValue(vcptr) / vcptr->getMaxVal();
}

int HumanEnemy::usePercentConsumable(Consumable *cons)
{
    vector<ValuedComponent *> vcs = cons->getValueComponents();
    int sum = 0;
    for (ValuedComponent *vc : vcs)
    {
        sum += effectiveValue(vc);
    }
    return sum / vcs.size();
}

int Human::effectiveValue(ValuedComponent *vcptr)
{
    if (auto ptr = dynamic_cast<Stat::HealthComponent *>(vcptr))
    {
        return min(vcptr->getMaxVal() + hp, max_hp);
    }
    else if (auto ptr = dynamic_cast<Stat::StaminaComponent *>(vcptr))
    {
        return min(vcptr->getMaxVal() + combat_tokens, max_combat_tokens);
    }
}

int DamageComponent::simulateDamage(Entity *entity)
{
    return entity->calculateDmg(*this);
}

// view module for enemies (entities in general)
namespace view
{
    string info(Entity *entity)
    {
        return entity->getinfo();
    }

    vector<string> showrelics()
    {
        vector<string> available_relics = {};
        for (bool i : relics)
        {
            if (i)
            {
                available_relics.push_back(relicDescriptions[i]);
            }
        }
        return (available_relics);
    }

    vector<string> getNames(vector<Item *> items)
    {
        vector<string> names = {};
        for (Item *i : items)
        {
            names.push_back(i->getname());
        }
        return names;
    }

    vector<vector<string>> getvv(vector<Item *> items)
    {
        vector<vector<string>> descsvect = {};
        for (Item *i : items)
        {
            descsvect.push_back(i->getDesc());
        }
        return descsvect;
    }

    vector<string> getdescs(vector<Item *> items)
    {
        vector<vector<string>> descsvect = {};
        for (Item *i : items)
        {
            descsvect.push_back(i->getDesc());
        }
        vector<string> descscs = {};
        for (vector<string> d : descsvect)
        {
            string s = "";
            for (int i = 0; i < d.size(); i++)
            {
                s.append(d[i]);
            }
            descscs.push_back(s);
        }
        return descscs;
    }
    string getDescLine(vector<string> vstring)
    {
        string s = "";
        for (int i = 0; i < vstring.size(); i++)
        {
            s.append(vstring[i]);
        }
        return s;
    }

}
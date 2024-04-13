#include <vector>
#include "combatfornow.hpp"
using namespace std;
using namespace utils;

//premade items for shops and characters to use
struct Items
{
public:
    static vector<Item *> getAllPossibleItems()
    {
        vector<Item *> items = {};
        items.push_back(new Consumable("Peanut Butter Sandwich", {new Stat::HealthComponent(10)}, {}, {"Heals 10 HP. ", "Looking at it fills you with nostalgia, so much that you don't want to use it. "}, nullptr, 1)); // a whole poem, long and big. makes you sick, relieve the sweat, how hasn't it melted yet, unless you hold it out for too long in which case it might? idk.
        items.push_back(new Consumable("Pancake", {new Stat::HealthComponent(10)}, {}, {"Heals 10 Hp.", "Looking at this makes you feel special. Just not enough to make you want to keep it."}, nullptr, 1));            // a whole poem, long and big. makes you sick, relieve the sweat, how hasn't it melted yet, unless you hold it out for too long in which case it might? idk.
        items.push_back(new Consumable("Popsicle", {}, {DamageComponent(0, DamageComponent::TYPE::ice)}, {"Puts out burn.", "inflicts freeze.", "Popsicle, Popsicle, blows yo"}, nullptr, 1));                            // a whole poem, long and big. makes you sick, relieve the sweat, how hasn't it melted yet, unless you hold it out for too long in which case it might? idk.
        items.push_back(new Consumable("Health Kit", {new Stat::HealthComponent(20)}, {}, {"Heals 20 HP.", "Band-Aid and some magical spray!"}, nullptr, 1));
        items.push_back(new Consumable("Round Candy", {new Stat::StaminaComponent(1)}, {}, {"Increases stamina. ", "Super sweet, super energizing! no wonder mom hid them all for herself"}, nullptr, 0));
        items.push_back(new Consumable("Grenade", {}, {DamageComponent(8, DamageComponent::TYPE::explosion)}, {"Deals 30 damage.", "You don't remember where you found this."}, nullptr, 1));
        items.push_back(new FireArm("Laser Gun", {DamageComponent(4, DamageComponent::TYPE::fire)}, {"Deals 4 damage.", "Inflicts burn. ", "It reminds you of simpler times."}, 10, 10, nullptr, 1)); // a blue laser and a fire laser
        items.push_back(new FireArm("Blue Laser Gun", {DamageComponent(5, DamageComponent::TYPE::ice)}, {"Deals 4 damage. ", "Inflicts freeze. ", "A modern model. \"The Implications of the cold future.\""}, 10, 10, nullptr, 1));
        items.push_back(new Melee("Baseball Bat", {DamageComponent(3)}, {"Deals 5 regular damage. ", "Decorated with way too many pink things."}, nullptr, 2));
        items.push_back(new FireArm("Devil's Gaze", {DamageComponent(7, DamageComponent::TYPE::fire)}, {"Deals 7 damage. ", "Inflicts burn. ", "Ever wonder how he looks without his glasses? "}, 10, 10, nullptr, 1));
        return items;
    }
}; // add an icecream store that sells as many icecreams as you want.

// Factory functions for enemies
namespace Enemies
{ //! couldn't figure out why these get created with default constructors, like why all have 100 hp and such.
    Enemy *gethusk(int lvl, int luck, string weaponname = "weapon")
    {
        string str = "you take your trusty " + weaponname + ", and get ready for a(n easy) fight!";
        return new Zombie("Common Husk", 12, roll(2) ? "male" : "female", lvl, (5 * lvl) + 3 * roll(luck), 3 + lvl, "", "fire", {"the zombie Rooaarrrs!!!", " but not nearly loud enough to scare a man like you.", str, "~"});
    }
    Enemy *getjug(int lvl, int luck)
    {
        return new Zombie("Juggernaut", 12, "can't tell", lvl, (8 * lvl) + 9 * roll(luck), 5 + lvl, "", "fire", {});
    }
    Enemy *getnerd(int lvl, int luck)
    {
        HumanEnemy *heptr = new HumanEnemy("Bitten Nerd", 12, roll(2) ? "male" : "female", lvl, (6 * lvl) + 7 * roll(luck), 0.6 * lvl, {Items::getAllPossibleItems()[3], Items::getAllPossibleItems()[4], Items::getAllPossibleItems()[5]}, {"He has a familiar face. "});
        heptr->setMelee(dynamic_cast<Weapon *>(Items::getAllPossibleItems()[8]));
        heptr->setfirearm(dynamic_cast<Weapon *>(Items::getAllPossibleItems()[9]));
        return heptr;
    }
    Enemy *getghoul(int lvl, int luck)
    {
        return new Zombie("Common ghoul", 12, "can't tell", lvl, (5 * lvl) + 7 * roll(luck), 3 + lvl, "regular", "", {"Your regular attacks phase (almost) right through! "});
    }
};
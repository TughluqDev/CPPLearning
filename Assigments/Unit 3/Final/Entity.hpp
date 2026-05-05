#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "Item.hpp"
using namespace std;

// fire>air>earth>water>fire
enum class Element
{
    None,
    Fire,
    Water,
    Earth,
    Air
};

// ANSI color codes, just strings you stick in cout before text and reset after
// works on Windows 10+ terminal and VS Code, gotta call enableColors() in main first tho
namespace Color
{
    const string RED = "\033[91m";
    const string GREEN = "\033[92m";
    const string YELLOW = "\033[93m";
    const string BLUE = "\033[94m";
    const string CYAN = "\033[96m";
    const string WHITE = "\033[97m";
    const string GRAY = "\033[90m"; // dark gray for empty bar slots
    const string RESET = "\033[0m"; // back to default color
    const string BOLD = "\033[1m";  // bold text
}

// short 5char label for alignment in the status display
inline string elementLabel(Element e)
{
    switch (e)
    {
    case Element::Fire:
        return "Fire ";
    case Element::Water:
        return "Water";
    case Element::Earth:
        return "Earth";
    case Element::Air:
        return "Air  ";
    default:
        return "None ";
    }
}

// maps each element to a matching color so fire looks red, water looks blue etc
inline string elementColor(Element e)
{
    switch (e)
    {
    case Element::Fire:
        return Color::RED;
    case Element::Water:
        return Color::BLUE;
    case Element::Earth:
        return Color::YELLOW;
    case Element::Air:
        return Color::CYAN;
    default:
        return Color::WHITE;
    }
}

// bar color changes as hp drops green is fine, yellow is low, red is almost ded
inline string hpColor(int hp, int maxHp)
{
    if (maxHp <= 0)
        return Color::RED;
    // float division so we get a real percentage not integer 0 or 1
    float pct = (float)hp / maxHp;
    if (pct > 0.5f)
        return Color::GREEN;
    if (pct > 0.25f)
        return Color::YELLOW;
    return Color::RED;
}

// returns damage multiplier for an attacker/defender element pair
inline float elementMod(Element atk, Element def)
{
    if (atk == Element::None || def == Element::None || atk == def)
        return 1.0f;
    // super effective matchups which does 1.5x damage
    if ((atk == Element::Fire && def == Element::Air) ||
        (atk == Element::Air && def == Element::Earth) ||
        (atk == Element::Earth && def == Element::Water) ||
        (atk == Element::Water && def == Element::Fire))
        return 1.5f;
    // not very effective matchups 0.75x less damage
    if ((atk == Element::Air && def == Element::Fire) ||
        (atk == Element::Earth && def == Element::Air) ||
        (atk == Element::Water && def == Element::Earth) ||
        (atk == Element::Fire && def == Element::Water))
        return 0.75f;
    return 1.0f; // if it is the same element or unrelated pair
}

// entity is the base class for all chracters, and they inherit all its attributes, stats are set to private and only accesables with getters
class Entity
{
private:
    string name;
    int hp;
    int maxHp;
    int attackDmg;
    int defense;
    int speed;
    int critChance;
    Element element;
    vector<Item> inventory;

public:
    Entity(const string &n, int hp_, int atk, int def, int spd, int crit = 10, Element elem = Element::None) : name(n), hp(hp_), maxHp(hp_), attackDmg(atk), defense(def), speed(spd), critChance(crit), element(elem) {}

    // one line function getters bcs im suppa lazy
    string getName() const { return name; }
    int getHp() const { return hp; }
    int getMaxHp() const { return maxHp; }
    int getAttack() const { return attackDmg; }
    int getDefense() const { return defense; }
    int getSpeed() const { return speed; }
    int getCritChance() const { return critChance; }
    Element getElement() const { return element; }
    bool isAlive() const { return hp > 0; }
    const vector<Item> &getInventory() const { return inventory; }

    // mutators
    void addItem(const Item &item) { inventory.push_back(item); }
    void takeDamage(int dmg) { hp = max(0, hp - dmg); }
    void restore(int amount) { hp = min(maxHp, hp + amount); }

    // all combat code, includes dodge, base damage, elemental mods and crits
    int attackTarget(Entity &target)
    {
        // higher target speed = higher dodge chance, hard capped at 30% so nobody is immune
        int dodgeChance = min(target.speed / 3, 30);
        if ((rand() % 100) < dodgeChance)
        {
            cout << "  " << Color::CYAN << target.name << " dodged " << name << "'s attack!" << Color::RESET << "\n";
            return 0;
        }

        // base damage: attacker dmg minus targets defense, minimum 1 so u always do something
        int dmg = max(1, attackDmg - target.defense);

        // next we apply the element match up so strong or weak elements change the damage
        float mod = elementMod(element, target.element);
        dmg = max(1, static_cast<int>(dmg * mod));

        // after that the crit roll checks if this hit gets one more damage boost
        bool crit = (rand() % 100) < critChance;
        if (crit)
            dmg = max(1, static_cast<int>(dmg * 1.5f));

        target.takeDamage(dmg);

        // attack messages with colors for effectiveness and crits
        cout << "  " << name << " attacks " << target.name << " for " << Color::YELLOW << dmg << " dmg" << Color::RESET;
        if (mod > 1.0f)
            cout << " " << Color::GREEN << "Super effective!" << Color::RESET;
        if (mod < 1.0f)
            cout << " " << Color::BLUE << "Not very effective" << Color::RESET;
        if (crit)
            cout << " " << Color::BOLD << Color::YELLOW << "CRIT!" << Color::RESET;
        cout << "\n";

        return dmg;
    }

    // uses item at itemIndex from this entity's inventory on target.
    bool useItemOn(int itemIndex, Entity &target)
    {
        if (itemIndex < 0 || itemIndex >= (int)inventory.size())
            return false;

        // copy values before erasing the item so we still have em after the erase
        string itemName = inventory[itemIndex].getName();
        int amount = inventory[itemIndex].getHealAmount();

        target.restore(amount);
        cout << "  " << name << " used " << Color::GREEN << itemName << Color::RESET << " on " << target.name;
        if (amount > 0)
            cout << " (" << Color::GREEN << "+" << amount << " HP" << Color::RESET << ")";
        cout << "!\n";

        // erase removes the item from the vector so it cant be used again
        inventory.erase(inventory.begin() + itemIndex);
        return true;
    }

    // prints out stats with a 20 char HP bar
    void showStatus() const
    {
        const int BAR = 20;
        // turn hp into a number of filled blocks so the bar matches the health left
        int filled = maxHp > 0 ? (hp * BAR) / maxHp : 0;
        string barCol = hpColor(hp, maxHp);
        string elemCol = elementColor(element);

        // adds spaces to short names so all the labels line up better on screen
        string padded = name;
        while ((int)padded.size() < 10)
            padded += ' ';

        cout << padded << "  " << Color::WHITE << "Element:" << Color::RESET << "[" << elemCol << elementLabel(element) << Color::RESET << "]" << "  " << Color::CYAN << "Health Bar:" << Color::RESET << "[";
        // prints one block at a time so filled hp and empty space can use different colors
        for (int i = 0; i < BAR; i++)
        {
            if (i < filled)
                cout << barCol << '#';
            else
                cout << Color::GRAY << '-';
        }
        cout << Color::RESET << "]"
             << " " << Color::WHITE << "HP:" << Color::RESET << " " << barCol << hp << "/" << maxHp << Color::RESET
             << " " << Color::WHITE << "Attack:" << Color::RESET << attackDmg
             << " " << Color::WHITE << "Defense:" << Color::RESET << defense
             << " " << Color::WHITE << "Speed:" << Color::RESET << speed;
    }
};

#endif

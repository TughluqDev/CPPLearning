#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
using namespace std;

//if heal amount is more than 0 it heals but if it is negative it does damge like for potion throws
class Item {
private:
    string name;
    int healAmount;

public:
    Item(const string& n, int heal): name(n), healAmount(heal) {}

    //one line function gettas cuz im suppa lazy
    string getName() const { return name; }
    int getHealAmount() const { return healAmount; }
};

#endif

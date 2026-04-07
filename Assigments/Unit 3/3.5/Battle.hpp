#ifndef BATTLE_HPP
#define BATTLE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Entity {
private:
    string name;
    int hp;
    int maxHp;
    int attackDmg;
    int critChance;

public:
    Entity(string n, int h, int a, int crit = 15)
        : name(n), hp(h), maxHp(h), attackDmg(a), critChance(crit) {}

    string getName() const{ 
        return name; 
    }
    int getHp() const {
        return hp; 
    }
    int getMaxHp() const {
        return maxHp; 
    }
    int getAttackDmg() const { 
        return attackDmg; 
    }
    bool isAlive() const { 
        return hp > 0; 
    }

    void takeDamage(int dmg) {
        hp -= dmg;
        if (hp < 0) hp = 0;
    }

    int attack(Entity& target) {
        int dmg = attackDmg;
        bool crit = (rand() % 100) < critChance;
        if (crit) dmg = static_cast<int>(dmg * 1.5);

        target.takeDamage(dmg);

        cout << name << " attacks " << target.getName()
             << " for " << dmg << " damage";
        if (crit) cout << " (CRITICAL HIT!)";
        cout << endl;

        return dmg;
    }

    void showHealthBar() const {
        int barLen = 20;
        int filled = 0;
        if (maxHp > 0) filled = (hp * barLen) / maxHp;

        cout << name << " [";
        for (int i = 0; i < barLen; i++) {
            cout << (i < filled ? "▮" : "-");
        }
        cout << "] " << hp << "/" << maxHp << endl;
    }
};

#endif
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

class Character {
private:
    int hp;
    int attack;
    int maxHp;

public:
    Character(int hp, int attack) : hp(hp), attack(attack), maxHp(hp) {}

    int getHp() const;
    int getAttack() const;
    void takeDamage(int damage);
    bool isAlive() const;

    void showHealthBar(const std::string& name) const;
};

class Player : public Character {
public:
    Player(int hp, int attack) : Character(hp, attack) {}
};

class Enemy : public Character {
public:
    Enemy(int hp, int attack) : Character(hp, attack) {}
};

#endif
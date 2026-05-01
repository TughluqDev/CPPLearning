#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

class Enemy : public Entity {
public:
    Enemy(const string& n, int hp, int atk, int def, int spd,int crit = 8, Element elem = Element::None): Entity(n, hp, atk, def, spd, crit, elem) {}

    //bad guy presets
    static Enemy createGoblin() {
        return Enemy("Goblin", 30, 8, 2, 18, 8, Element::Earth);
    }

    static Enemy createFireDrake() {
        return Enemy("Fire Drake", 45, 16, 4, 15, 12, Element::Fire);
    }

    static Enemy createOrc() {
        return Enemy("Orc", 55, 13,  8,  5, 10, Element::Earth);
    }

    static Enemy createSeaSerpent() {
        return Enemy("Sea Serpent", 40, 10,  6, 10, 10, Element::Water);
    }
};

#endif
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

//player is a subclass of entity representing a player character
//3 presets of chracters: waririor (tank), rougue(supa fast), mage(glass cananon)
class Player : public Entity {
public:
    Player(const string& n, int hp, int atk, int def, int spd,
           int crit, Element elem)
        : Entity(n, hp, atk, def, spd, crit, elem) {}


    //slow but hard to kill
    static Player createWarrior(const string& name = "Warrior") {
        Player p(name, 120, 14, 10, 8, 10, Element::Earth);
        p.addItem(Item("Health Potion", 35));
        p.addItem(Item("Health Potion", 35));
        return p;
    }

    //fastest character which means it has high crit and doge chance
    static Player createRogue(const string& name = "Rogue") {
        Player p(name, 75, 16, 4, 22, 30, Element::Air);
        p.addItem(Item("Adrenaline Shot", 20));
        p.addItem(Item("Bandage", 15));
        return p;
    }

    //lota damage but loooow health
    static Player createMage(const string& name = "Mage") {
        Player p(name, 65, 24, 2, 13, 20, Element::Fire);
        p.addItem(Item("Elixir", 45));
        p.addItem(Item("Health Potion", 30));
        return p;
    }
};

#endif

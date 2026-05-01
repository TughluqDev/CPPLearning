#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Character.hpp"

using namespace std;

int Character::getHp() const {
    return hp;
}

int Character::getAttack() const {
    return attack;
}

void Character::takeDamage(int damage) {
    hp -= damage;
}

bool Character::isAlive() const {
    return hp > 0;
}

void Character::showHealthBar(const string& name) const {
    int maxBars = 20;
    int bars = (hp > 0) ? (hp * maxBars / maxHp) : 0;

    cout << name << " HP: ";

    for (int i = 0; i < bars; i++)
        cout << "▮";

    for (int i = bars; i < maxBars; i++)
        cout << "-";

    cout << " (" << hp << ")" << std::endl;
}

int main() {
    ::srand(time(0));

    Player player(100, 15);
    Enemy enemy(80, 12);

    while (player.isAlive() && enemy.isAlive()) {

        int playerDamage = player.getAttack();
        if (rand() % 100 < 20) {
            playerDamage *= 2;
            cout << "CRITICAL HIT! ";
        }

        enemy.takeDamage(playerDamage);
        cout << "Naser attacks for " << playerDamage << std::endl;

        if (!enemy.isAlive()) break;

        int enemyDamage = enemy.getAttack();
        player.takeDamage(enemyDamage);
        cout << "Peter attacks for " << enemyDamage << std::endl;

        player.showHealthBar("Naser");
        enemy.showHealthBar("Peter");

    }

    if (player.isAlive())
        cout << "Naser Wins!" << std::endl;
    else
        cout << "Peter Wins!" << std::endl;

}
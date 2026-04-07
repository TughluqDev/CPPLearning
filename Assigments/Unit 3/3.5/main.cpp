#include "Battle.hpp"

void battleOneAtATime(Entity& player, vector<Entity>& enemies) {
    cout << "ONE AT A TIME MODE" << endl << endl;

    for (int i = 0; i < enemies.size(); i++) {
        cout << player.getName() << " vs " << enemies[i].getName() << endl;

        while (player.isAlive() && enemies[i].isAlive()) {
            player.attack(enemies[i]);
            if (!enemies[i].isAlive()) {
                cout << enemies[i].getName() << " is defeated!" << endl;
                break;
            }

            enemies[i].attack(player);
            if (!player.isAlive()) {
                cout << player.getName() << " has died!" << endl;
                break;
            }

            player.showHealthBar();
            enemies[i].showHealthBar();
            cout << endl;
        }

        if (!player.isAlive()) break;
        cout << endl;
    }

    cout << (player.isAlive() ? "Player wins!" : "Enemies win!") << endl;
}

void battleAllAtOnce(Entity& player, vector<Entity>& enemies) {
    cout << "ALL AT ONCE MODE" << endl << endl;
    int turn = 1;

    while (player.isAlive()) {
        bool anyAlive = false;
        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i].isAlive()) { anyAlive = true; break; }
        }
        if (!anyAlive) break;

        cout << "Turn " << turn++ << "" << endl;
        player.showHealthBar();
        cout << "Enemies:" << endl;
        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i].isAlive()) {
                cout << "  " << i + 1 << ") ";
                enemies[i].showHealthBar();
            }
        }

        int choice = -1;
        while (true) {
            cout << "Choose enemy to attack (1-" << enemies.size() << "): ";
            cin >> choice;
            choice--;
            if (choice >= 0 && choice < enemies.size() && enemies[choice].isAlive())
                break;
            cout << "Invalid choice." << endl;
        }

        player.attack(enemies[choice]);
        if (!enemies[choice].isAlive())
            cout << enemies[choice].getName() << " is defeated!" << endl;

        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i].isAlive()) {
                enemies[i].attack(player);
                if (!player.isAlive()) {
                    cout << player.getName() << " has fallen!" << endl;
                    break;
                }
            }
        }
        cout << endl;
    }

    cout << (player.isAlive() ? "Player wins!" : "Enemies win!") << endl;
}

int main() {
    srand(time(0));

    vector<Entity> enemies;
    enemies.push_back(Entity("Goblin",   12, 3, 10));
    enemies.push_back(Entity("Skeleton", 10, 4, 10));
    enemies.push_back(Entity("Slime",     8, 2,  5));

    Entity player("Hero", 50, 8, 20);

    cout << "Select mode:" << endl;
    cout << "1: Battle enemies one at a time" << endl;
    cout << "2: Battle all enemies at once (choose targets)" << endl;
    cout << "Choice: ";
    int mode;
    cin >> mode;
    cout << endl;

    if (mode == 2) {
        battleAllAtOnce(player, enemies);
    } else {
        battleOneAtATime(player, enemies);
    }

}
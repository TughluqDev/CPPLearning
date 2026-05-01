#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "Player.hpp"
#include "Enemy.hpp"

using namespace std;

//returns true if any entity in the container is still alive
bool anyAlive(const vector<Player>& party) {
    for (auto& p : party) if (p.isAlive()) return true;
    return false;
}

bool anyAlive(const vector<Enemy>& enemies) {
    for (auto& e : enemies) if (e.isAlive()) return true;
    return false;
}

//returns a random alive index or -1 if all are dead
int randomAliveIdx(const vector<Player>& party) {
    vector<int> alive;
    //first gather only living party members so the random pick stays valid
    for (int i = 0; i < (int)party.size(); i++)
        if (party[i].isAlive()) alive.push_back(i);
    return alive.empty() ? -1 : alive[rand() % alive.size()];
}

int randomAliveIdx(const vector<Enemy>& enemies) {
    vector<int> alive;
    //does the same thing for enemies, build a list of alive indexes then roll from it
    for (int i = 0; i < (int)enemies.size(); i++)
        if (enemies[i].isAlive()) alive.push_back(i);
    return alive.empty() ? -1 : alive[rand() % alive.size()];
}

//returns the highest speed value among alive members of a container
template<typename T>
int maxSpeed(const vector<T>& group) {
    int s = 0;
    for (auto& x : group) if (x.isAlive()) s = max(s, x.getSpeed());
    return s;
}

//all display code
void showBattleStatus(const vector<Player>& party, int activeIdx, const vector<Enemy>& enemies) {
    cout << "\nPARTY\n";
    for (int i = 0; i < (int)party.size(); i++) {
        //marks active character with [*] others with spaces
        cout << (i == activeIdx ? " [*] " : "     ");
        party[i].showStatus();
        if (!party[i].isAlive()) cout << "  [DEAD]";
        else if (i == activeIdx) cout << "  <ACTIVE>";
        cout << "\n";
    }

    cout << "\nENEMIES\n";
    for (int i = 0; i < (int)enemies.size(); i++) {
        cout << "  " << (i + 1) << ") ";
        if (enemies[i].isAlive()) {
            enemies[i].showStatus();
        } else {
            cout << enemies[i].getName() << " [DEFEATED]";
        }
        cout << "\n";
    }
    cout << "\n";
}


//asks the player to select a live enemy target; loops until valid
int pickEnemyTarget(const vector<Enemy>& enemies) {
    while (true) {
        cout << "  Pick target:\n";
        for (int i = 0; i < (int)enemies.size(); i++)
            if (enemies[i].isAlive())
                cout << "    " << (i + 1) << ") " << enemies[i].getName() << "\n";
        cout << "  > ";
        int choice; cin >> choice; choice--;
        if (choice >= 0 && choice < (int)enemies.size() && enemies[choice].isAlive())
            return choice;
        cout << "  Invalid choice. Try again.\n";
    }
}

//akss the player to switch to a different alive party member and returns currentIdx unchanged if the input is invalid
int pickSwitch(const vector<Player>& party, int currentIdx) {
    cout << "  Switch to:\n";
    for (int i = 0; i < (int)party.size(); i++)
        if (i != currentIdx && party[i].isAlive())
            cout << "    " << (i + 1) << ") " << party[i].getName() << "\n";
    cout << "  > ";
    int choice; cin >> choice; choice--;
    if (choice >= 0 && choice < (int)party.size() &&
        choice != currentIdx && party[choice].isAlive())
        return choice;
    cout << "  Invalid — keeping current active.\n";
    return currentIdx;
}


//controls the active character's action which is either attack, use item or switch active after switching, the new active still acts this tur and returns the maybe updated activeIdx.
int playerTurn(vector<Player>& party, int activeIdx, vector<Enemy>& enemies) {
    Player& active = party[activeIdx];

    cout << active.getName() << "'s turn:\n";
    cout << "1) Attack\n";
    cout << "2) Use Item" << (active.getInventory().empty() ? " (empty)" : "") << "\n";
    cout << "3) Switch Active Character\n";

    int action; cin >> action;
    cout << "\n";

    switch (action) {

        case 1: {
            //normie attack and player picks target enemy
            int t = pickEnemyTarget(enemies);
            active.attackTarget(enemies[t]);
            if (!enemies[t].isAlive())
                cout << "  >> " << enemies[t].getName() << " is defeated!\n";
            break;
        }

        case 2: {
            const auto& inv = active.getInventory();
            if (inv.empty()) {
                cout << "  No items — attacking instead.\n";
                int t = pickEnemyTarget(enemies);
                active.attackTarget(enemies[t]);
                if (!enemies[t].isAlive())
                    cout << "  >> " << enemies[t].getName() << " is defeated!\n";
                break;
            }

            //show each item with its heal amount so the player can compare them fast
            cout << "  Items:\n";
            for (int i = 0; i < (int)inv.size(); i++)
                cout << "    " << (i + 1) << ") "
                     << inv[i].getName() << " (+" << inv[i].getHealAmount() << " HP)\n";

            //items can only be used on living teammates so dead ones are skipped
            cout << "  Use on which party member?\n";
            for (int i = 0; i < (int)party.size(); i++)
                if (party[i].isAlive())
                    cout << "    " << (i + 1) << ") " << party[i].getName() << "\n";

            cout << "  Item #: ";   int itemIdx;   cin >> itemIdx;   itemIdx--;
            cout << "  Member #: "; int memberIdx; cin >> memberIdx; memberIdx--;
            cout << "\n";

            if (memberIdx >= 0 && memberIdx < (int)party.size() && party[memberIdx].isAlive())
                active.useItemOn(itemIdx, party[memberIdx]);
            else
                cout << "  Invalid target — item wasted.\n";
            break;
        }

        case 3: {
            //switch active the new character then attacks this turn
            activeIdx = pickSwitch(party, activeIdx);
            if (anyAlive(enemies)) {
                int t = pickEnemyTarget(enemies);
                party[activeIdx].attackTarget(enemies[t]);
                if (!enemies[t].isAlive())
                    cout << "  >> " << enemies[t].getName() << " is defeated!\n";
            }
            break;
        }

        default: {
            cout << "Unrecognised input attacking random enemy.\n";
            int t = randomAliveIdx(enemies);
            if (t >= 0) {
                active.attackTarget(enemies[t]);
                if (!enemies[t].isAlive())
                    cout << "  >> " << enemies[t].getName() << " is defeated!\n";
            }
            break;
        }
    }

    return activeIdx;
}

//all non active alive paty members auto-attack a random live enemy
void allyAutoAttack(vector<Player>& party, int activeIdx, vector<Enemy>& enemies) {
    for (int i = 0; i < (int)party.size(); i++) {
        if (i == activeIdx || !party[i].isAlive()) continue;
        int t = randomAliveIdx(enemies);
        if (t < 0) break; //no enemies left
        cout << "Auto ";
        party[i].attackTarget(enemies[t]);
        if (!enemies[t].isAlive())
            cout << "  >> " << enemies[t].getName() << " is defeated!\n";
    }
}

//all alive enemies attack a random alive party member
void enemyTurn(vector<Enemy>& enemies, vector<Player>& party) {
    for (auto& enemy : enemies) {
        if (!enemy.isAlive()) continue;
        int t = randomAliveIdx(party);
        if (t < 0) break; //party wiped
        enemy.attackTarget(party[t]);
        if (!party[t].isAlive())
            cout << "  >> " << party[t].getName() << " has fallen!\n";
    }
}



//runs a full party-vs-enemies battle and speed determines which side acts first each round tout les allies attack every round et tout les enemies attack every round, player picks their target
void runBattle(vector<Player>& party, int activeIdx, vector<Enemy>& enemies) {
    cout << "BATTLE START!\n";
    int turn = 0;
    while (anyAlive(party) && anyAlive(enemies)) {
        cout << "\nTurn " << ++turn <<"\n";
        showBattleStatus(party, activeIdx, enemies);
        //the side with the highest living speed stat gets to move first this round
        bool partyFirst = maxSpeed(party) >= maxSpeed(enemies);
        cout << (partyFirst ? "Your party moves first!\n" : "Enemies move first!\n") << "\n";

        if (partyFirst) {
            //party acts and then enemies if there are anyy leftttttt
            activeIdx = playerTurn(party, activeIdx, enemies);
            if (anyAlive(enemies)) allyAutoAttack(party, activeIdx, enemies);

            if (anyAlive(party) && anyAlive(enemies)) {
                cout << "\nEnemies turn \n";
                enemyTurn(enemies, party);
            }
        } else {
            //enemies act first amd then party if there are any left
            cout << "Enemies' turn\n";
            enemyTurn(enemies, party);

            if (anyAlive(party) && anyAlive(enemies)) {
                cout << "\nYour turn\n";
                activeIdx = playerTurn(party, activeIdx, enemies);
                if (anyAlive(enemies)) allyAutoAttack(party, activeIdx, enemies);
            }
        }

        //if the lead character goes down we swap to another living teammate right away
        if (!party[activeIdx].isAlive()) {
            int next = randomAliveIdx(party);
            if (next >= 0) {
                cout << "\n" << party[activeIdx].getName() << " is down! " << party[next].getName() << " takes the lead.\n";
                activeIdx = next;
            }
        }
    }

    //end of the battle summary 
    if (anyAlive(party)) {
        cout << " YOUR PARTY WINS! you won an easy game, good job?\n";
        cout << "Survivors:\n";
        for (auto& p : party) {
            if (p.isAlive()) { cout << "  "; p.showStatus(); cout << "\n"; }
        }
    } else {
        cout << "YOUR PARTY HAS FALLEN...skill issue lmao how did u loose😹😹😹\n";
    }
}

#endif

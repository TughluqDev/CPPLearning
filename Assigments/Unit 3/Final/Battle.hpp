#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "Player.hpp"
#include "Enemy.hpp"

using namespace std;

// using the colors from Entity.hpp for all the menus and text

// checks if anyone is still alive in a vector
template <typename T>
bool anyAlive(const vector<T> &group)
{
    for (auto &x : group)
        if (x.isAlive())
            return true;
    return false;
}

// picks a random alive index returns -1 if everyones dead
template <typename T>
int randomAliveIdx(const vector<T> &group)
{
    vector<int> alive;
    // get all alive indexes first so we dont accidentally pick a dead guy
    for (int i = 0; i < (int)group.size(); i++)
        if (group[i].isAlive())
            alive.push_back(i);
    return alive.empty() ? -1 : alive[rand() % alive.size()];
}

// finds the highest speed among alive members in the group
template <typename T>
int maxSpeed(const vector<T> &group)
{
    int s = 0;
    for (auto &x : group)
        if (x.isAlive())
            s = max(s, x.getSpeed());
    return s;
}

// shows everyones current stats and hp bars
void showBattleStatus(const vector<Player> &party, int activeIdx, const vector<Enemy> &enemies)
{
    cout << "\n"
         << Color::BOLD << Color::GREEN << "PARTY" << Color::RESET << "\n";
    for (int i = 0; i < (int)party.size(); i++)
    {
        // marks active character with [*] others with spaces
        cout << (i == activeIdx ? " " + Color::CYAN + "[*]" + Color::RESET + "  " : "     ");
        party[i].showStatus();
        if (!party[i].isAlive())
            cout << "  " << Color::RED << "[DEAD]" << Color::RESET;
        else if (i == activeIdx)
            cout << "  " << Color::CYAN << "<ACTIVE>" << Color::RESET;
        cout << "\n";
    }

    cout << "\n"
         << Color::BOLD << Color::RED << "ENEMIES" << Color::RESET << "\n";
    for (int i = 0; i < (int)enemies.size(); i++)
    {
        cout << "  " << Color::YELLOW << (i + 1) << ")" << Color::RESET << " ";
        if (enemies[i].isAlive())
        {
            enemies[i].showStatus();
        }
        else
        {
            cout << enemies[i].getName() << " " << Color::GRAY << "[DEFEATED]" << Color::RESET;
        }
        cout << "\n";
    }
    cout << "\n";
}

// player picks an enemy to attack, keeps looping if they type something invalid
int pickEnemyTarget(const vector<Enemy> &enemies)
{
    while (true)
    {
        cout << "  " << Color::WHITE << "Pick target:" << Color::RESET << "\n";
        for (int i = 0; i < (int)enemies.size(); i++)
            if (enemies[i].isAlive())
                cout << "    " << Color::YELLOW << (i + 1) << ")" << Color::RESET << " " << enemies[i].getName() << "\n";
        cout << "  " << Color::CYAN << ">" << Color::RESET << " ";
        int choice;
        cin >> choice;
        choice--;
        if (choice >= 0 && choice < (int)enemies.size() && enemies[choice].isAlive())
            return choice;
        cout << "  " << Color::RED << "Invalid choice try again" << Color::RESET << "\n";
    }
}

// lets the player swap which character theyre controlling
int pickSwitch(const vector<Player> &party, int currentIdx)
{
    cout << "  " << Color::WHITE << "Switch to:" << Color::RESET << "\n";
    for (int i = 0; i < (int)party.size(); i++)
        if (i != currentIdx && party[i].isAlive())
            cout << "    " << Color::YELLOW << (i + 1) << ")" << Color::RESET << " " << party[i].getName() << "\n";
    cout << "  " << Color::CYAN << ">" << Color::RESET << " ";
    int choice;
    cin >> choice;
    choice--;
    if (choice >= 0 && choice < (int)party.size() &&
        choice != currentIdx && party[choice].isAlive())
        return choice;
    cout << "  " << Color::RED << "Invalid choice keeping current active" << Color::RESET << "\n";
    return currentIdx;
}

// handles what the player does on their turn, attack or use item or switch character
int playerTurn(vector<Player> &party, int activeIdx, vector<Enemy> &enemies)
{
    Player &active = party[activeIdx];

    cout << Color::BOLD << Color::CYAN << active.getName() << "'s turn:" << Color::RESET << "\n";
    cout << Color::YELLOW << "1)" << Color::RESET << " Attack\n";
    cout << Color::YELLOW << "2)" << Color::RESET << " Use Item" << (active.getInventory().empty() ? " " + Color::GRAY + "(empty)" + Color::RESET : "") << "\n";
    cout << Color::YELLOW << "3)" << Color::RESET << " Switch Active Character\n";

    int action;
    cin >> action;
    cout << "\n";

    switch (action)
    {

    case 1:
    {
        // normie attack and player picks target enemy
        int t = pickEnemyTarget(enemies);
        active.attackTarget(enemies[t]);
        if (!enemies[t].isAlive())
            cout << "  >> " << enemies[t].getName() << " is defeated!\n";
        break;
    }

    case 2:
    {
        const auto &inv = active.getInventory();
        if (inv.empty())
        {
            cout << "  " << Color::GRAY << "No items, attacking instead." << Color::RESET << "\n";
            int t = pickEnemyTarget(enemies);
            active.attackTarget(enemies[t]);
            if (!enemies[t].isAlive())
                cout << "  >> " << enemies[t].getName() << " is defeated!\n";
            break;
        }

        // list out all items and what they do so the player can pick
        cout << " " << Color::GREEN << "Items:" << Color::RESET << "\n";
        for (int i = 0; i < (int)inv.size(); i++)
        {
            int amount = inv[i].getHealAmount();
            cout << " " << Color::YELLOW << (i + 1) << ")" << Color::RESET << " " << inv[i].getName() << " ";
            if (amount >= 0)
                cout << Color::GREEN << "(+" << amount << " HP)" << Color::RESET;
            else
                cout << Color::RED << "(" << -amount << " dmg)" << Color::RESET;
            cout << "\n";
        }

        cout << "  " << Color::WHITE << "Item #:" << Color::RESET << " ";
        int itemIdx;
        cin >> itemIdx;
        itemIdx--;
        cout << "\n";

        if (itemIdx < 0 || itemIdx >= (int)inv.size())
        {
            cout << "  " << Color::RED << "Invalid item." << Color::RESET << "\n";
            break;
        }

        int amount = inv[itemIdx].getHealAmount();

        // heal items still go on teammates but damage items now get aimed at enemies
        if (amount >= 0)
        {
            cout << " " << Color::WHITE << "Use on which party member?" << Color::RESET << "\n";
            for (int i = 0; i < (int)party.size(); i++)
                if (party[i].isAlive())
                    cout << "    " << Color::YELLOW << (i + 1) << ")" << Color::RESET << " " << party[i].getName() << "\n";

            cout << "  " << Color::WHITE << "Member #:" << Color::RESET << " ";
            int memberIdx;
            cin >> memberIdx;
            memberIdx--;
            cout << "\n";

            // make sure the selected ally is valid before using the item on them
            if (memberIdx >= 0 && memberIdx < (int)party.size() && party[memberIdx].isAlive())
                active.useItemOn(itemIdx, party[memberIdx]);
            else
                cout << "  " << Color::RED << "Invalid target, item wasted." << Color::RESET << "\n";
        }
        else
        {
            int enemyIdx = pickEnemyTarget(enemies);
            active.useItemOn(itemIdx, enemies[enemyIdx]);
            if (!enemies[enemyIdx].isAlive())
                cout << "  >> " << enemies[enemyIdx].getName() << " is defeated!\n";
        }
        break;
    }

    case 3:
    {
        // switch then still attack so the whole turn isnt just wasted on swapping
        activeIdx = pickSwitch(party, activeIdx);
        if (anyAlive(enemies))
        {
            int t = pickEnemyTarget(enemies);
            party[activeIdx].attackTarget(enemies[t]);
            if (!enemies[t].isAlive())
                cout << "  >> " << enemies[t].getName() << " is defeated!\n";
        }
        break;
    }

    default:
    {
        cout << Color::RED << "Unrecognised input, attacking random enemy." << Color::RESET << "\n";
        int t = randomAliveIdx(enemies);
        if (t >= 0)
        {
            active.attackTarget(enemies[t]);
            if (!enemies[t].isAlive())
                cout << "  >> " << enemies[t].getName() << " is defeated!\n";
        }
        break;
    }
    }

    return activeIdx;
}

// the other party members auto attack while u control the active one
void allyAutoAttack(vector<Player> &party, int activeIdx, vector<Enemy> &enemies)
{
    for (int i = 0; i < (int)party.size(); i++)
    {
        if (i == activeIdx || !party[i].isAlive())
            continue;
        int t = randomAliveIdx(enemies);
        if (t < 0)
            break; // no enemies left
        cout << Color::GRAY << "Auto " << Color::RESET;
        party[i].attackTarget(enemies[t]);
        if (!enemies[t].isAlive())
            cout << "  >> " << enemies[t].getName() << " is defeated!\n";
    }
}

// each enemy attacks a random party member
void enemyTurn(vector<Enemy> &enemies, vector<Player> &party)
{
    for (auto &enemy : enemies)
    {
        if (!enemy.isAlive())
            continue;
        // each enemy picks their own random target so they dont all just attack the same person
        int t = randomAliveIdx(party);
        if (t < 0)
            break; // party wiped #awkwardgamermoment
        enemy.attackTarget(party[t]);
        if (!party[t].isAlive())
            cout << "  >> " << party[t].getName() << " has fallen!\n";
    }
}

// main battle loop, keeps going until one side is wiped out
void runBattle(vector<Player> &party, int activeIdx, vector<Enemy> &enemies)
{
    cout << Color::BOLD << Color::RED << "BATTLE START!" << Color::RESET << "\n";
    int turn = 0;
    while (anyAlive(party) && anyAlive(enemies))
    {
        cout << "\n"
             << Color::BOLD << Color::WHITE << "Turn " << ++turn << Color::RESET << "\n";
        showBattleStatus(party, activeIdx, enemies);
        // whoever has the highest speed goes first this round
        bool partyFirst = maxSpeed(party) >= maxSpeed(enemies);
        cout << (partyFirst ? Color::GREEN + string("Your party moves first!\n") : Color::RED + string("Enemies move first!\n")) << Color::RESET << "\n";

        if (partyFirst)
        {
            // party acts and then enemies if there are anyy leftttttt
            activeIdx = playerTurn(party, activeIdx, enemies);
            if (anyAlive(enemies))
                allyAutoAttack(party, activeIdx, enemies);

            if (anyAlive(party) && anyAlive(enemies))
            {
                cout << "\n"
                     << Color::RED << "Enemies turn" << Color::RESET << "\n";
                enemyTurn(enemies, party);
            }
        }
        else
        {
            // enemies went first so now its the party's turn if anyone is still up
            cout << Color::RED << "Enemies' turn" << Color::RESET << "\n";
            enemyTurn(enemies, party);

            if (anyAlive(party) && anyAlive(enemies))
            {
                cout << "\n"
                     << Color::GREEN << "Your turn" << Color::RESET << "\n";
                activeIdx = playerTurn(party, activeIdx, enemies);
                if (anyAlive(enemies))
                    allyAutoAttack(party, activeIdx, enemies);
            }
        }

        // if the active char dies auto swap to someone who is still alive
        if (!party[activeIdx].isAlive())
        {
            int next = randomAliveIdx(party);
            if (next >= 0)
            {
                cout << "\n"
                     << Color::YELLOW << party[activeIdx].getName() << Color::RESET << " is down! " << Color::CYAN << party[next].getName() << Color::RESET << " takes the lead.\n";
                activeIdx = next;
            }
        }
    }

    // show who won and print the survivors
    if (anyAlive(party))
    {
        cout << Color::BOLD << Color::GREEN << "YOUR PARTY WINS!" << Color::RESET << " you won an easy game, good job?\n";
        cout << Color::WHITE << "Survivors:" << Color::RESET << "\n";
        for (auto &p : party)
        {
            if (p.isAlive())
            {
                cout << "  ";
                p.showStatus();
                cout << "\n";
            }
        }
    }
    else
    {
        cout << Color::BOLD << Color::RED << "YOUR PARTY HAS FALLEN..." << Color::RESET << " skill issue lmao how did u loose\n";
    }
}

#endif
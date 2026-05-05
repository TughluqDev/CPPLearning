#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "Player.hpp"
#include "Enemy.hpp"

using namespace std;

// battle text also uses the color strings from Entity so menus and labels pop more

// returns true if any entity in the container is still alive
bool anyAlive(const vector<Player> &party)
{
    for (auto &p : party)
        if (p.isAlive())
            return true;
    return false;
}

bool anyAlive(const vector<Enemy> &enemies)
{
    for (auto &e : enemies)
        if (e.isAlive())
            return true;
    return false;
}

// returns a random alive index or -1 if all are dead
int randomAliveIdx(const vector<Player> &party)
{
    vector<int> alive;
    // first gather only living party members so the random pick stays valid
    for (int i = 0; i < (int)party.size(); i++)
        if (party[i].isAlive())
            alive.push_back(i);
    return alive.empty() ? -1 : alive[rand() % alive.size()];
}

int randomAliveIdx(const vector<Enemy> &enemies)
{
    vector<int> alive;
    // does the same thing for enemies, build a list of alive indexes then roll from it
    for (int i = 0; i < (int)enemies.size(); i++)
        if (enemies[i].isAlive())
            alive.push_back(i);
    return alive.empty() ? -1 : alive[rand() % alive.size()];
}

// returns the highest speed value among alive members of a container
template <typename T>
int maxSpeed(const vector<T> &group)
{
    int s = 0;
    for (auto &x : group)
        if (x.isAlive())
            s = max(s, x.getSpeed());
    return s;
}

// all display code
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

// asks the player to select a live enemy target; loops until valid
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

// asks the player to switch to a different alive party member and returns currentIdx unchanged if the input is invalid
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

// controls the active character's action which is either attack, use item or switch active after switching, the new active still acts this tur and returns the maybe updated activeIdx.
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

        // show each item with its heal amount so the player can compare them fast
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

            // the item call already checks the item index, here we only make sure the teammate exists
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
        // switch active then use the new character right away so the turn is not wasted
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

// all non active alive paty members auto-attack a random live enemy
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

// all alive enemies attack a random alive party member
void enemyTurn(vector<Enemy> &enemies, vector<Player> &party)
{
    for (auto &enemy : enemies)
    {
        if (!enemy.isAlive())
            continue;
        // every enemy rolls its own random target so they do not all dogpile the same one every time
        int t = randomAliveIdx(party);
        if (t < 0)
            break; // party wiped
        enemy.attackTarget(party[t]);
        if (!party[t].isAlive())
            cout << "  >> " << party[t].getName() << " has fallen!\n";
    }
}

// runs a full party-vs-enemies battle and speed determines which side acts first each round tout les allies attack every round et tout les enemies attack every round, player picks their target
void runBattle(vector<Player> &party, int activeIdx, vector<Enemy> &enemies)
{
    cout << Color::BOLD << Color::RED << "BATTLE START!" << Color::RESET << "\n";
    int turn = 0;
    while (anyAlive(party) && anyAlive(enemies))
    {
        cout << "\n"
             << Color::BOLD << Color::WHITE << "Turn " << ++turn << Color::RESET << "\n";
        showBattleStatus(party, activeIdx, enemies);
        // the side with the highest living speed stat gets to move first this round
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
            // enemies act first amd then party if there are any left
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

        // if the lead character goes down we swap to another living teammate right away
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

    // end of the battle summary
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

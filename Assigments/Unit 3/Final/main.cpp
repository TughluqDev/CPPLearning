#include <ctime>
#include <filesystem>
#include <windows.h>
#include <mmsystem.h>
#include "Battle.hpp"

#pragma comment(lib, "winmm.lib")

//starts the battle music from this folder and loops it until we stop it
static void startBattleMusic() {
    filesystem::path musicPath = filesystem::path(__FILE__).parent_path() /
        "Pokémon Red, Blue & Yellow - Trainer Battle Music (HQ) - Pokeli (128k).mp3";
    string command = "open \"" + musicPath.string() + "\" type mpegvideo alias battleMusic";
    mciSendStringA("close battleMusic", nullptr, 0, nullptr);
    mciSendStringA(command.c_str(), nullptr, 0, nullptr);
    mciSendStringA("play battleMusic repeat", nullptr, 0, nullptr);
}

//stops the music and closes the file after the battle is over
static void stopBattleMusic() {
    mciSendStringA("stop battleMusic", nullptr, 0, nullptr);
    mciSendStringA("close battleMusic", nullptr, 0, nullptr);
}

//prints a starting chracters preset stats and items
static void printPreset(const Player& p, int num) {
    cout << "  " << num << ") ";
    p.showStatus();
    cout << "\n     Items: ";
    for (auto& item : p.getInventory())
        cout << item.getName() << "  ";
    cout << "\n\n";
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    //title and some basic info
    cout << "TURN-BASED BATTLE GAME\n";
    cout << "Element chart(attacker > defender = 1.5x damage):\n";
    cout << "Fire > Air > Earth > Water > Fire\n\n";

    //all three presets are in the party, the player just picks which one they control as the active character.
    Player warrior = Player::createWarrior();
    Player rogue = Player::createRogue();
    Player mage = Player::createMage();

    cout << "CHOOSE YOUR ACTIVE CHARACTER (all three will fight):\n\n";
    printPreset(warrior, 1);
    printPreset(rogue, 2);
    printPreset(mage, 3);

    cout << "Start with which character active? (1/2/3): ";
    int pick; cin >> pick;
    if (pick < 1 || pick > 3) pick = 1;
    int activeIdx = pick - 1;

    //builds party and enemy group
    vector<Player> party = { warrior, rogue, mage };

    //a spread of elements and stat builds for all bad guys
    vector<Enemy> enemies = {
        Enemy::createGoblin(),
        Enemy::createFireDrake(),
        Enemy::createOrc()
    };

    //starts music right before the fight and turns it off when the fight ends
    startBattleMusic();
    runBattle(party, activeIdx, enemies);
    stopBattleMusic();
}

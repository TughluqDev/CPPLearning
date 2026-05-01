#include <ctime>
#include <string>
#include <windows.h>
#include <mmsystem.h>
#include "Battle.hpp"

using MciSendStringWFn = MCIERROR (WINAPI *)(LPCWSTR, LPWSTR, UINT, HANDLE);

//loads winmm only when we need music so g++ does not need an extra linker flag
//btw im never implementing music ever again, its super cool but soooooo annoyingggg 😭😭
static MciSendStringWFn getMciSendString() {
    static HMODULE winmm = LoadLibraryW(L"winmm.dll");
    static MciSendStringWFn mciSend = winmm ? reinterpret_cast<MciSendStringWFn>(GetProcAddress(winmm, "mciSendStringW")) : nullptr;
    return mciSend;
}

//turns on ansi colors in newer windows terminals so the color strings actually show right
static void enableColors() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (out == INVALID_HANDLE_VALUE) return;

    DWORD mode = 0;
    if (!GetConsoleMode(out, &mode)) return;

    //virtual terminal mode is what makes ansi escape codes work on windows
    SetConsoleMode(out, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

//looks for the first mp3 in this folder so the code still works even if the file name is weird
static wstring findMusicFile() {
    WIN32_FIND_DATAW findData;
    HANDLE findHandle = FindFirstFileW(L"*.mp3", &findData);
    if (findHandle == INVALID_HANDLE_VALUE) return L"";
    FindClose(findHandle);

    //the search only checks this exe folder so the first mp3 we find is good enough
    return findData.cFileName;
}

//starts the battle music from this folder and loops it until we stop it
static void startBattleMusic() {
    MciSendStringWFn mciSend = getMciSendString();
    if (!mciSend) return;

    wstring musicPath = findMusicFile();
    if (musicPath.empty()) return;

    //wide strings keep weird file name chars safe so mci can still open the song
    wstring command = L"open \"" + musicPath + L"\" type mpegvideo alias battleMusic";
    mciSend(L"close battleMusic", nullptr, 0, nullptr);
    if (mciSend(command.c_str(), nullptr, 0, nullptr) == 0)
        mciSend(L"play battleMusic repeat", nullptr, 0, nullptr);
}

//stops the music and closes the file after the battle is over
static void stopBattleMusic() {
    MciSendStringWFn mciSend = getMciSendString();
    if (!mciSend) return;

    mciSend(L"stop battleMusic", nullptr, 0, nullptr);
    mciSend(L"close battleMusic", nullptr, 0, nullptr);
}

//prints a starting chracters preset stats and items
static void printPreset(const Player& p, int num) {
    cout << "  " << Color::YELLOW << num << ")" << Color::RESET << " ";
    p.showStatus();
    cout << "\n" << Color::GREEN << "Items:" << Color::RESET << " ";
    for (auto& item : p.getInventory())
        cout << item.getName() << "  ";
    cout << "\n\n";
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    enableColors();
    startBattleMusic();

    //title and some basic info
    cout << Color::BOLD << Color::WHITE << "TURN-BASED BATTLE GAME" << Color::RESET << "\n";

    cout << Color::WHITE << "Element chart" << Color::RESET << " " << Color::GRAY << "(attacker > defender = 1.5x damage)" << Color::RESET << ":\n";

    cout << Color::RED << "Fire" << Color::RESET << " > "
        << Color::CYAN << "Air" << Color::RESET << " > "
        << Color::YELLOW << "Earth" << Color::RESET << " > "
        << Color::BLUE << "Water" << Color::RESET << " > "
        << Color::RED << "Fire" << Color::RESET << "\n\n";

    //all three presets are in the party, the player just picks which one they control as the active character.
    Player warrior = Player::createWarrior();
    Player rogue = Player::createRogue();
    Player mage = Player::createMage();

    cout << Color::BOLD << Color::GREEN << "CHOOSE YOUR ACTIVE CHARACTER" << Color::RESET << " " << Color::GRAY << "(all three will fight)" << Color::RESET << ":\n\n";
    printPreset(warrior, 1);
    printPreset(rogue, 2);
    printPreset(mage, 3);

    cout << Color::WHITE << "Start with which character active?" << Color::RESET << " " << Color::GRAY << "(1/2/3)" << Color::RESET << ": ";
    int pick; cin >> pick;
    if (pick < 1 || pick > 3) pick = 1;
    int activeIdx = pick - 1;

    //builds party and enemy group
    vector<Player> party = { warrior, rogue, mage };

    //a spread of elements and stat builds for all bad guys
    vector<Enemy> enemies = {
        Enemy::createGoblin(),
        Enemy::createFireDrake(),
        Enemy::createOrc(),
        Enemy::createSeaSerpent()
    };

    runBattle(party, activeIdx, enemies);
    stopBattleMusic();
}

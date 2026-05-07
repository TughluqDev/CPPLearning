#include <ctime>
#include <string>
#include <windows.h>
#include <mmsystem.h>
#include "Battle.hpp"

using MciSendStringWFn = MCIERROR(WINAPI *)(LPCWSTR, LPWSTR, UINT, HANDLE);

// lazy loads winmm so i dont have to add -lwinmm to the g++ command every time
// btw im never implementing music ever again, its super cool but soooooo annoyingggg 😭😭
static MciSendStringWFn getMciSendString()
{
    static HMODULE winmm = LoadLibraryW(L"winmm.dll");
    static MciSendStringWFn mciSend = winmm ? reinterpret_cast<MciSendStringWFn>(GetProcAddress(winmm, "mciSendStringW")) : nullptr;
    return mciSend;
}

static void enableColors()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (out == INVALID_HANDLE_VALUE)
        return;

    DWORD mode = 0;
    if (!GetConsoleMode(out, &mode))
        return;

    SetConsoleMode(out, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

// searches for any mp3 in the current folder because the actual file name is way too long to hardcode and im too lazy to rename it
static wstring findMusicFile()
{
    WIN32_FIND_DATAW findData;
    HANDLE findHandle = FindFirstFileW(L"*.mp3", &findData);
    if (findHandle == INVALID_HANDLE_VALUE)
        return L"";
    FindClose(findHandle);

    return findData.cFileName;
}

// plays the music and loops it the whole time
static void startBattleMusic()
{
    MciSendStringWFn mciSend = getMciSendString();
    if (!mciSend)
        return;

    wstring musicPath = findMusicFile();
    if (musicPath.empty())
        return;

    // mci needs wide strings or it breaks on the special chars in the pokemon file name lol
    wstring command = L"open \"" + musicPath + L"\" type mpegvideo alias battleMusic";
    mciSend(L"close battleMusic", nullptr, 0, nullptr);
    if (mciSend(command.c_str(), nullptr, 0, nullptr) == 0)
        mciSend(L"play battleMusic repeat", nullptr, 0, nullptr);
}

// stop the music when the battle ends
static void stopBattleMusic()
{
    MciSendStringWFn mciSend = getMciSendString();
    if (!mciSend)
        return;

    mciSend(L"stop battleMusic", nullptr, 0, nullptr);
    mciSend(L"close battleMusic", nullptr, 0, nullptr);
}

// prints a starting chracters preset stats and items
static void printPreset(const Player &p, int num)
{
    cout << "  " << Color::YELLOW << num << ")" << Color::RESET << " ";
    p.showStatus();
    cout << "\n"
         << Color::GREEN << "Items:" << Color::RESET << " ";
    for (auto &item : p.getInventory())
        cout << item.getName() << "  ";
    cout << "\n\n";
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    enableColors();
    startBattleMusic();

    // game title and element chart
    cout << Color::BOLD << Color::WHITE << "TURN-BASED BATTLE GAME" << Color::RESET << "\n";

    cout << Color::WHITE << "Element chart" << Color::RESET << " " << Color::GRAY << "(attacker > defender = 1.5x damage)" << Color::RESET << ":\n";

    cout << Color::RED << "Fire" << Color::RESET << " > "
         << Color::CYAN << "Air" << Color::RESET << " > "
         << Color::YELLOW << "Earth" << Color::RESET << " > "
         << Color::BLUE << "Water" << Color::RESET << " > "
         << Color::RED << "Fire" << Color::RESET << "\n\n";

    Player warrior = Player::createWarrior();
    Player rogue = Player::createRogue();
    Player mage = Player::createMage();

    cout << Color::BOLD << Color::GREEN << "CHOOSE YOUR ACTIVE CHARACTER" << Color::RESET << " " << Color::GRAY << "(all three will fight)" << Color::RESET << ":\n\n";
    printPreset(warrior, 1);
    printPreset(rogue, 2);
    printPreset(mage, 3);

    cout << Color::WHITE << "Start with which character active?" << Color::RESET << " " << Color::GRAY << "(1/2/3)" << Color::RESET << ": ";
    int pick;
    cin >> pick;
    if (pick < 1 || pick > 3)
        pick = 1;
    int activeIdx = pick - 1;

    vector<Player> party = {warrior, rogue, mage};

    vector<Enemy> enemies = {
        Enemy::createGoblin(),
        Enemy::createFireDrake(),
        Enemy::createOrc(),
        Enemy::createSeaSerpent()};

    runBattle(party, activeIdx, enemies);
    stopBattleMusic();
}

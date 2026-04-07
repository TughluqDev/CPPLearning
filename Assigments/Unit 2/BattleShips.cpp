#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 10;
const char WATER = '~';
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';

void displayBoard(const vector<vector<char>>& board, bool showShips = false) {
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
    }
    cout << "\n";

    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == SHIP && !showShips) {
                cout << WATER << " ";
            } else {
                cout << board[i][j] << " ";
            }
        }
        cout << "\n";
    }
}

void manualPlaceShips(vector<vector<char>>& board, int playerNumber) {
    int shipsPlaced = 0;

    cout << "\n=== PLAYER " << playerNumber << " PLACE YOUR SHIPS ===\n";

    while (shipsPlaced < 5) {
        displayBoard(board, true);

        int row, col;
        cout << "Enter row for ship #" << shipsPlaced + 1 << ": ";
        cin >> row;
        cout << "Enter column: ";
        cin >> col;

        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
            cout << "Invalid coordinates! Try again.\n";
            continue;
        }

        if (board[row][col] == SHIP) {
            cout << "Ship already placed there! Try again.\n";
            continue;
        }

        board[row][col] = SHIP;
        shipsPlaced++;
    }

    cout << "Ships placed successfully!\n";
}

bool attack(vector<vector<char>>& opponentBoard,
            vector<vector<char>>& attackBoard,
            int row, int col) {

    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        cout << "Invalid coordinates!\n";
        return false;
    }

    if (attackBoard[row][col] != WATER) {
        cout << "Already attacked here!\n";
        return false;
    }

    if (opponentBoard[row][col] == SHIP) {
        attackBoard[row][col] = HIT;
        opponentBoard[row][col] = HIT; 
        cout << "HIT!\n";
    } else {
        attackBoard[row][col] = MISS;
        cout << "MISS!\n";
    }

    return true; 
}

int c ountShips(const vector<vector<char>>& board) {
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == SHIP) count++;
        }
    }
    return count;
}

int main() {

    vector<vector<char>> board1(BOARD_SIZE, vector<char>(BOARD_SIZE, WATER));
    vector<vector<char>> board2(BOARD_SIZE, vector<char>(BOARD_SIZE, WATER));
    vector<vector<char>> attackBoard1(BOARD_SIZE, vector<char>(BOARD_SIZE, WATER));
    vector<vector<char>> attackBoard2(BOARD_SIZE, vector<char>(BOARD_SIZE, WATER));

    cout << "=== BATTLESHIP GAME ===\n";


    manualPlaceShips(board1, 1);
    cout << string(50, '\n'); 

    manualPlaceShips(board2, 2);
    cout << string(50, '\n');


    int turn = 1;

    while (countShips(board1) > 0 && countShips(board2) > 0) {

        bool validMove = false;

        while (!validMove) {

            if (turn == 1) {
                cout << "\n PLAYER 1's TURN\n";
                displayBoard(attackBoard1);

                int row, col;
                cout << "Enter row: ";
                cin >> row;
                cout << "Enter column: ";
                cin >> col;

                validMove = attack(board2, attackBoard1, row, col);
                if (validMove) turn = 2;

            } else {
                cout << "\nPLAYER 2's TURN\n";
                displayBoard(attackBoard2);

                int row, col;
                cout << "Enter row: ";
                cin >> row;
                cout << "Enter column: ";
                cin >> col;

                validMove = attack(board1, attackBoard2, row, col);
                if (validMove) turn = 1;
            }
        }
    }


    if (countShips(board1) == 0) {
        cout << "\n PLAYER 2 WINS! \n";
    } else {
        cout << "\n PLAYER 1 WINS! \n";
    }
}
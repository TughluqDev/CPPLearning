#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<vector<string>> board;

    for (int row = 1; row <= 10; row++)
    {
        vector<string> currentRow;

        for (char col = 'A'; col <= 'J'; col++)
        {
            currentRow.push_back(string(1, col) + to_string(row));
        }

        board.push_back(currentRow);
    }

    for (const auto& row : board)
    {
        for (const auto& cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }

    return 0;
}
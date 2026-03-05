#include <iostream>
#include <vector>

using namespace std; 

int main()
{
    vector<vector<int>> numbers;
    
    int value = 1;

    for (int row = 0; row < 10; row++)
    {
        vector<int> currentRow;

        for (int col = 0; col < 5; col++)
        {
            currentRow.push_back(value);
            value += 2; 
        }

        numbers.push_back(currentRow);
    }

    for (const auto& row : numbers)
    {
        for (int num : row)
        {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
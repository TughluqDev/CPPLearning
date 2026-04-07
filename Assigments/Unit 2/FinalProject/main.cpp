#include <iostream>
#include "Einstien.hpp"

using namespace std;

int main()
{
    cout << factorial(5) << endl;

    cout << combination(5, 2) << endl;

    cout << gcd(12, 18) << endl;

    vector<int> gcdNums = {24,36,60};
    cout << lcmRecursive(4, 6) << endl;

    vector<vector<int>> table = multiplicationTable();
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << table[i][j] << "\t";
        }
        cout << endl;
    }

    vector<int> numbers = {5, 2, 9, 2, 7, 5, 2};

    cout << "\nMax: " << findMax(numbers) << endl;
    cout << "Mean: " << calculateMean(numbers) << endl;
    cout << "Median: " << calculateMedian(numbers) << endl;

    cout << decimalToBinary(10) << endl;

    cout << binaryToDecimal("1010") << endl;


}
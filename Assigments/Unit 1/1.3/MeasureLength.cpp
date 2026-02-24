#include <iostream>
#include <string>
#include <limits>
#include <cmath>

using namespace std;

int main() {

    string input;
    cout << "Enter a number: ";
    cin >> input;

    bool hasDecimal = (input.find('.') != string::npos);

    int digitCount = 0;
    for (char c : input) {
        if (isdigit(c)) digitCount++;
    }

    bool isNegative = (!input.empty() && input[0] == '-');

    if (hasDecimal) {

        long double value = stold(input);

        if (digitCount <= 7) {
            float x = (float)value;
            cout << "Type: float\n";
        }
        else if (digitCount <= 15) {
            double x = (double)value;
            cout << "Type: double\n";
        }
        else {
            long double x = value;
            cout << "Type: long double\n";
        }

        cout << "String length: " << input.length() << endl;
    }

    else {

        long long value = stoll(input);

        if (!isNegative) {

            if (digitCount == 1) {
                char x = (char)value;
                cout << "Type: char\n";
            }
            else if (value <= numeric_limits<unsigned short>::max()) {
                unsigned short x = (unsigned short)value;
                cout << "Type: unsigned short\n";
            }
            else if (value <= numeric_limits<unsigned int>::max()) {
                unsigned int x = (unsigned int)value;
                cout << "Type: unsigned int\n";
            }
            else {
                unsigned long long x = (unsigned long long)value;
                cout << "Type: unsigned long long\n";
            }
        }

        else {

            if (value >= numeric_limits<short>::min() &&
                value <= numeric_limits<short>::max()) {

                short x = (short)value;
                cout << "Type: short\n";
            }
            else if (value >= numeric_limits<int>::min() &&
                     value <= numeric_limits<int>::max()) {

                int x = (int)value;
                cout << "Type: int\n";
            }
            else {
                long long x = value;
                cout << "Type: long long\n";
            }
        }

        cout << "String length: " << input.length() << endl;
    }

}

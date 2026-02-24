#include <iostream>
using namespace std;

int main() {
    int num;

    cout << "Enter a number: ";
    cin >> num;

    bool isEven = (num % 2 == 0);
    bool isNegative = (num < 0);

    if ( (isEven && !isNegative) || (!isEven && isNegative) ) {
        cout << num << " success";
    } else {
        cout << num << " fail";
    }

    return 0;
}

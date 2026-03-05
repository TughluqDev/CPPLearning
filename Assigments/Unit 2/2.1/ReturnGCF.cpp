#include <iostream>
using namespace std;

int findGCF(int a, int b) {
    a = abs(a);
    b = abs(b);
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

int main() {
    int num1 = 48;
    int num2 = 18;
    
    cout << "GCF of " << num1 << " and " << num2 << " is: " << findGCF(num1, num2) << endl;
    
    return 0;
}
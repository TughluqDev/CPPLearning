#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the position in Fibonacci sequence: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Please enter a positive number." << endl;
        return 1;
    }
    
    if (n == 1 || n == 2) {
        cout << "The " << n << "th Fibonacci number is: 1" << endl;
        return 0;
    }
    
    int fib1 = 1, fib2 = 1, fibN;
    for (int i = 3; i <= n; i++) {
        fibN = fib1 + fib2;
        fib1 = fib2;
        fib2 = fibN;
    }
    
    cout << "The " << n << "th Fibonacci number is: " << fibN << endl;
    return 0;
}
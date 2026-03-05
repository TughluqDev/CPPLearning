#include <iostream>

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int num = 5;
    std::cout << num << "! = " << factorial(num) << std::endl;
    return 0;
}
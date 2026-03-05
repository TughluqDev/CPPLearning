#include <iostream>
#include <vector>
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

int findGCF(int a, int b, int c) {
    return findGCF(findGCF(a, b), c);
}

int findGCF(const vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }
    
    int result = abs(nums[0]);
    for (size_t i = 1; i < nums.size(); i++) {
        result = findGCF(result, nums[i]);
    }
    
    return result;
}

int main() {
    int num1 = 48;
    int num2 = 18;
    
    cout << "GCF of " << num1 << " and " << num2 << " is: " << findGCF(num1, num2) << endl;
    cout << "GCF of 48, 18, and 30 is: " << findGCF(48, 18, 30) << endl;
    cout << "GCF of {24, 36, 60, 12} is: " << findGCF({24, 36, 60, 12}) << endl;
    
    return 0;
}

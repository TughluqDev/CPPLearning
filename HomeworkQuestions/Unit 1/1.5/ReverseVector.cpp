#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> numbers;
    int input;
    
    cout << "Enter numbers (enter -1 to stop):\n";
    while (true) {
        cin >> input;
        if (input == -1) break;
        numbers.push_back(input);
    }
    
    if (numbers.empty()) {
        cout << "No numbers entered.\n";
        return 0;
    }
    
    int maxElement = *max_element(numbers.begin(), numbers.end());
    int minElement = *min_element(numbers.begin(), numbers.end());
    
    cout << "\nVector in reverse order: ";
    for (int i = numbers.size() - 1; i >= 0; --i) {
        cout << numbers[i] << " ";
    }
    
    cout << "\n\nMaximum element: " << maxElement;
    cout << "\nMinimum element: " << minElement << "\n";
    
    return 0;
}
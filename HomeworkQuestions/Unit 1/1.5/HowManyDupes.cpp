#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    vector<int> array = {1, 2, 1, 3, 2};
    
    unordered_map<int, int> count;
    int duplicates = 0;
    
    for (int num : array) {
        count[num]++;
    }
    
    for (auto& pair : count) {
        if (pair.second > 1) {
            duplicates += pair.second - 1;
        }
    }
    
    cout << "Number of duplicates: " << duplicates << endl;
    
    return 0;
}
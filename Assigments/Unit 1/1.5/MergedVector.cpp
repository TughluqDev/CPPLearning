#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> vec1 = {3, 1, 4, 1, 5};
    vector<int> vec2 = {2, 7, 1, 8, 2};
    
    vector<int> merged = vec1;
    merged.insert(merged.end(), vec2.begin(), vec2.end());
    
    sort(merged.begin(), merged.end());
    
    cout << "Merged and sorted vector: ";
    for (int num : merged) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
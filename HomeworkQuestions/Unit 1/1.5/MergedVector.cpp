#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> vec1 = {3, 1, 4, 1, 5};
    vector<int> vec2 = {2, 7, 1, 8, 2};
    
    vector<int> merged = vec1;
    merged.insert(merged.end(), vec2.begin(), vec2.end());
    
    std::sort(merged.begin(), merged.end());
    
    std::cout << "Merged and sorted vector: ";
    for (int num : merged) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
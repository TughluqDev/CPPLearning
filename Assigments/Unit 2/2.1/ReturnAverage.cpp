#include <vector>

double calculateAverage(const std::vector<double>& numbers) {
    if (numbers.empty()) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (double num : numbers) {
        sum += num;
    }
    
    return sum / numbers.size();
}
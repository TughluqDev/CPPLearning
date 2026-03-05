#include <vector>

float returnSum(const std::vector<float>& nums) {
    float sum = 0.0f;
    for (float num : nums) {
        sum += num;
    }
    return sum;
}

double returnSum(const std::vector<double>& nums) {
    double sum = 0.0;
    for (double num : nums) {
        sum += num;
    }
    return sum;
}
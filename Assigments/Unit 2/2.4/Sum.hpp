#ifndef SUM_HPP
#define SUM_HPP

#include <vector>

int sum(const std::vector<int>& vec) {
    int total = 0;
    for (int num : vec) {
        total += num;
    }
    return total;
}

#endif
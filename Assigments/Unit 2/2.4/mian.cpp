#include <iostream>
#include "VectorData.hpp"
#include "Sum.hpp"

int main()
{
    int result = sum(testData);

    std::cout << "Sum = " << result << std::endl;

    return 0;
}
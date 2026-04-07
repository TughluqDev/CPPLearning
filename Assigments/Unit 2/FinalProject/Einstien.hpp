#ifndef EINSTIEN_HPP
#define EINSTIEN_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

//calculating factorial
long long factorial(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1); //recrusion
    }
}

//combo
long long combination(int n, int r)
{
    if (r < 0 || r > n || n > 21)
    {
        return 0;
    }
    else
    {
        return factorial(n) / (factorial(r) * factorial(n - r));
    }
}

//gcd with euclidinao
int gcd(int x, int y)
{
    if (y == 0)
    {
        return x;
    }
    else
    {
        return gcd(y, x % y);
    }
}

//gcd with vecotr
int gcdVector(const std::vector<int>& values)
{
    if (values.empty())
    {
        return 0;
    }

    int result = values[0];

    for (size_t i = 1; i < values.size(); i++)
    {
        result = gcd(result, values[i]);
    }

    return result;
}

//lcm
int lcmRecursive(int x, int y, int multiple = 1)
{
    if ((multiple % x == 0) && (multiple % y == 0))
    {
        return multiple;
    }
    else
    {
        return lcmRecursive(x, y, multiple + 1);
    }
}

//multiplication table for little kids
std::vector<std::vector<int>> multiplicationTable()
{
    std::vector<std::vector<int>> table(10, std::vector<int>(10));

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            table[i][j] = (i + 1) * (j + 1);
        }
    }

    return table;
}

//dec to bi
std::string decimalToBinary(int number)
{
    if (number == 0)
    {
        return "0";
    }

    std::string binary = "";

    while (number > 0)
    {
        binary = std::to_string(number % 2) + binary;
        number /= 2;
    }

    return binary;
}

//bi to dec
int binaryToDecimal(const std::string& binary)
{
    int result = 0;

    for (char bit : binary)
    {
        result = result * 2 + (bit - '0');
    }

    return result;
}

//maximum list
int findMax(const std::vector<int>& values)
{
    if (values.empty())
    {
        return 0;
    }

    return *std::max_element(values.begin(), values.end());
}

//mean
double calculateMean(const std::vector<int>& values)
{
    if (values.empty())
    {
        return 0.0;
    }

    double sum = std::accumulate(values.begin(), values.end(), 0);
    return sum / values.size();
}

//median
double calculateMedian(std::vector<int> values)
{
    if (values.empty())
    {
        return 0.0;
    }

    std::sort(values.begin(), values.end());

    size_t size = values.size();

    if (size % 2 == 0)
    {
        return (values[size / 2 - 1] + values[size / 2]) / 2.0;
    }
    else
    {
        return values[size / 2];
    }
}

#endif

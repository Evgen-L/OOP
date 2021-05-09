#include <set>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

const string NO_PRIME_NUMBERS = "there are no prime numbers in this sequence";
const int MAX_UPPER_BOUND = 1000000;

vector<bool> GetPrimeNumbersList(int upperBound)
{
    vector<bool> result(upperBound + 1, true);
    result[0] = false;
    for (int i = 2; i * i <= upperBound; i++)
    {
        for (int j = i + i; j <= upperBound; j += i)
        {
            result[j] = false;
        }
    }
    return result;
}

set<int> GeneratePrimeNumbersSet(int upperBound)
{
    set<int> result;
    if (upperBound < 0 || MAX_UPPER_BOUND < upperBound)
    {
        return result;
    }

    vector<bool> primeNumbersList = GetPrimeNumbersList(upperBound);
    for (int i = 0; i < primeNumbersList.size(); i++)
    {
        if (primeNumbersList[i])
        {
            result.emplace(i);
        }
    }
    return result;
}

void printSet(set<int> set)
{
    if (set.size() == 0)
    {
        cout << NO_PRIME_NUMBERS;
    }
    for (int element : set)
    {
        cout << element << " ";
    }
    cout << endl;
}
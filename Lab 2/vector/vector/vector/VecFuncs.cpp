#include "VecFuncs.h"
#include <vector>
#include <algorithm>
#include <iomanip>

using Vector = vector<float>;
using namespace std;

const string CANNOT_DIVIDE_BY_ZERO = "The vector shoudn't contain 0, since cannot divide by 0\n";
void ReadVector(Vector& vector)
{
    float num;
    while (cin >> num)
    {
        vector.push_back(num);
        //cout << "num: " << num << endl;
    };
}

void MultiplyMaxDivideMinimum(Vector& vector)
{
    if (!vector.empty())
    {
        float min = *std::min_element(vector.begin(), vector.end());
        if (min == 0) 
        {
            cout << CANNOT_DIVIDE_BY_ZERO;
        }
        else 
        {
            float max = *std::max_element(vector.begin(), vector.end());
            transform(vector.begin(), vector.end(), vector.begin(), [max, min](float num) -> float {return num * max / min; });
        }
    }
}

void PrintSortVector(Vector vector)
{
    sort(vector.begin(), vector.end());
    for_each(vector.begin(), vector.end(), [](float num) {cout << fixed << setprecision(3) << num << " "; });
}
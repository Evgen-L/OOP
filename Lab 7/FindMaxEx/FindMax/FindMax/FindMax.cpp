// FindMax.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const string NAME = "Name: ";
const string HEIGHT = "Height: ";
const string WEIGHT = "Weight: ";
const string MAX_WEIGHT_SPORTSMAN = "Max weight sportsman:\n";
const string MAX_HEIGHT_SPORTSMAN = "Max height sportsman:\n";

struct Sportsman
{
	string name;
	int height;
	int weight;
};

template < typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less) 
{
	if (arr.empty())
		return false;

	auto max = arr.begin();
	for (auto element = arr.begin(); element != arr.end(); element++)
	{
		if (less(*max, *element))
			max = element;
	}
	maxValue = *max;
	return true;
}

void PrintSportsman(Sportsman& sportsman) 
{
	cout << NAME << sportsman.name << endl;
	cout << HEIGHT << sportsman.height << endl;
	cout << WEIGHT << sportsman.weight << endl << endl;
}

int main()
{
	vector<Sportsman> sportsmans;
	sportsmans.push_back({ "Evgeniy Liakishev Sportmanovish", 167, 57 });
	sportsmans.push_back({ "Kalen Dalinin NeSportmanovish", 165, 54 });
	sportsmans.push_back({ "Konstantin Dinastiev NoNamemovich", 166, 60 });
	Sportsman maxHeightSportsman;
	Sportsman maxWeightSportsman;
	cout << MAX_HEIGHT_SPORTSMAN;
	FindMax(sportsmans, maxHeightSportsman, [](Sportsman const& a, Sportsman const& b) {return a.height < b.height; });
	PrintSportsman(maxHeightSportsman);

	cout << MAX_WEIGHT_SPORTSMAN;
	FindMax(sportsmans, maxWeightSportsman, [](Sportsman const& a, Sportsman const& b) {return a.weight < b.weight; });
	PrintSportsman(maxWeightSportsman);
}


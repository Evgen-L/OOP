#include <iostream> 
#include <fstream>
#include <string>
#include <optional>
#include <array>
#include <stdlib.h>
#include <stack>

using namespace std;

const int MAX_SIZE = 100;
const string INC_INP = "Usege: Please entere correct input: <input file> <output file> <search string> <replace string>\n";
const string DOESNOT_EX = "File doesn't exist\n";
const string FAIL_WRITE_DATA_OUTP = "Failed to write data to output file\n";
const string NOT_READING_FILE = "Reading did not complete\n";

using Field = array<array<char, MAX_SIZE>, MAX_SIZE>;

struct Args
{
	string inPath;
	string outPath;
};

struct Point
{
	int x;
	int y;
};

optional <Args> ParseArgv(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << INC_INP << endl;
		return nullopt;
	}
	Args args;
	args.inPath = argv[1];
	args.outPath = argv[2];
	return args;
}

void InitializeField(Field& field)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			field[i][j] = ' ';
		}
	}
}

void GetFiel(string& inPath, Field& field)
{
	ifstream input(inPath);
	if (!input.is_open())
	{
		cout << DOESNOT_EX;
		exit(1);
	}

	string line;
	int numberLine = 0;
	while (getline(input, line) && numberLine < MAX_SIZE)
	{
		for (size_t i = 0; i < MAX_SIZE && i < line.length(); i++)
		{
			field[numberLine][i] = line[i];
		}
		numberLine++;
		if (input.bad())
		{
			cout << NOT_READING_FILE;
			exit(1);
		}
	}
}


void Draw(Field& field, Point& point)
{
	if (field[point.x][point.y] != 'O')
	{
		field[point.x][point.y] = '-';
	}
};

array<Point, 4> GetNeighborPoints(Point point)
{
	Point p1 = { point.x - 1, point.y }, p2 = { point.x, point.y - 1 },
		p3 = { point.x + 1, point.y }, p4 = { point.x, point.y + 1 };
	return { p1, p2, p3, p4 };
}

void AddNeighborPoints(stack<Point>& steck, Point& point, Field& field)
{
	steck.pop();
	array<Point, 4> neighborPoints = GetNeighborPoints(point);
	for (Point p : neighborPoints)
	{
		if ((p.x >= 0 && p.x < MAX_SIZE && p.y >= 0 && p.y < MAX_SIZE) && (field[p.x][p.y] == ' '))
		{
			steck.push(p);
		}
	}
}

void FillField(Point point, Field& field)
{
	stack<Point> steck;
	steck.push(point);
	while (!steck.empty())
	{
		Draw(field, steck.top());
		AddNeighborPoints(steck, steck.top(), field);
	}
}

void PutField(string& outPath, Field& field)
{
	ofstream output(outPath);
	if (!output.is_open())
	{
		cout << DOESNOT_EX;
		exit(1);
	}
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			output << field[i][j];
		}
		output << endl;
	}
	if (!output.flush())
	{
		cout << FAIL_WRITE_DATA_OUTP;
		exit(1);
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgv(argc, argv);
	if (!args)
	{
		return 1;
	}
	string inpPath = args->inPath;
	string outPath = args->outPath;
	Field field;
	InitializeField(field);
	GetFiel(inpPath, field);
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (field[i][j] == 'O')
			{
				FillField({ i, j }, field);
			}
		}
	}
	PutField(outPath, field);
	return 0;
}
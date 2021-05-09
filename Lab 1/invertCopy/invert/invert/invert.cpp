#include <iostream> 
#include <fstream>
#include <string>
#include <optional>
#include <array>
#include <sstream>
#include <stdlib.h>
#include <cmath>

using namespace std;
using Matrix3x3 = array<array<float, 3>, 3>;
using Matrix2x2 = array<array<float, 2>, 2>;

const int NOT_FOUD = string::npos;
const string INC_INP = "Usege: Please entere correct input: <input file> <output file> <search string> <replace string>\n";
const string DOESNOT_EX = "File doesn't exist\n";
const string FAIL_WRITE_DATA_OUTP = "Failed to write data to output file\n";
const string NOT_READING_FILE = "Reading did not complete\n";
const string DIGITS = "0123456789.- ";
const string INC_CHAR = "Extraneous characters\n";
const string FAIL_READ = "Failed to read number from file\n";
const string EXT_NUM = "You have extra number in line\n";
const string NUM_NOT_FOUND = "Numbers not found\n";
const string NULL_DET = "Determinant of this matrix is null. Can't invert this matrix.\n";
const string EXT_LINE = "Extra line in matrix\n";



struct Args
{
	string inPath;
};

optional <Args> ParseArgv(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << INC_INP << endl;
		return nullopt;
	}
	Args args;
	args.inPath = argv[1];
	return args;
}

void PrintMatrix(Matrix3x3& matrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%.3f ", abs(matrix[i][j]) < 0.0001 ? abs(matrix[i][j]) : matrix[i][j]);
		}
		cout << endl;
	}
};

void Print2x2(Matrix2x2 matrix)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
};

void GetMatrix(string inputPath, Matrix3x3& matrix) {
	ifstream input(inputPath);
	if (!input.is_open())
	{
		cout << DOESNOT_EX;
		exit(1);
	}

	for (int i = 0; i < 3; i++)
	{
		stringstream scanner;
		string line;
		getline(input, line);
		if (line.find_first_not_of(DIGITS) != NOT_FOUD)
		{
			cout << INC_CHAR << " Position is " << line.find_first_not_of(DIGITS);
			exit(1);
		}

		if (line.find_first_of(DIGITS) == NOT_FOUD)
		{
			cout << NUM_NOT_FOUND;
			exit(1);
		}

		scanner = (stringstream)line;
		for (int j = 0; j < 3; j++)
		{
			if (!(scanner >> matrix[i][j]))
			{
				cout << FAIL_READ;
				exit(1);
			}
		}

		if (!scanner.eof())
		{
			cout << EXT_NUM;
			exit(1);
		}
	}
	if (!input.eof())
	{
		cout << EXT_LINE;
		exit(1);
	}
	input.close();
}


float GetDeterminant3x3(Matrix3x3& matrix)
{
	float  determinant = matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[1][0] * matrix[2][1] * matrix[0][2]
		- matrix[0][2] * matrix[1][1] * matrix[2][0]
		- matrix[1][2] * matrix[2][1] * matrix[0][0]
		- matrix[0][1] * matrix[1][0] * matrix[2][2];
	return determinant;
}

void TransposeMatrix(Matrix3x3& matrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = i; j < 3; j++)
		{
			swap(matrix[j][i], matrix[i][j]);
		}
	}
};


Matrix2x2 GetMinor(Matrix3x3 matrix, int i, int j)
{
	int x = 0;
	int y = 0;
	Matrix2x2 minor = { 0 };
	for (int a = 0; a < 3; a++) {
		if (a != i)
		{
			for (int b = 0; b < 3; b++) {
				if (b != j)
				{
					minor[x][y] = matrix[a][b];
					if (y < 1)
					{
						y++;
					}
					else
					{
						y = 0;
						x++;
					}
				}
			}
		}

	};
	return minor;
}

float GetDeterminant2x2(Matrix2x2 matrix)
{
	return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
};

Matrix3x3 GetCoefficientMatrix(Matrix3x3& matrix)
{
	Matrix3x3 coeffMat;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			coeffMat[i][j] = (float)(GetDeterminant2x2(GetMinor(matrix, i, j)) * pow(-1, i + j));
		}
	}
	return coeffMat;
};

void InvertMatrix(Matrix3x3& matrix)
{
	float det3x3 = 0;
	det3x3 = GetDeterminant3x3(matrix);
	if (det3x3 == 0)
	{
		cout << NULL_DET;
		exit(1);
	}
	TransposeMatrix(matrix);
	Matrix3x3 coefftMat = GetCoefficientMatrix(matrix);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			coefftMat[i][j] /= det3x3;
		}
	}
	matrix = coefftMat;
}



int main(int argc, char* argv[])
{
	auto args = ParseArgv(argc, argv);
	if (!args)
	{
		return 1;
	}
	ifstream inFile;
	string inputPath = args->inPath;
	Matrix3x3 matrix = { 0 };
	GetMatrix(inputPath, matrix);
	InvertMatrix(matrix);
	PrintMatrix(matrix);
	return 0;
}
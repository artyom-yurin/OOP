#include <array>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

typedef array<array <float, 2>, 2> Matrix2;
typedef array<array <float, 3>, 3> Matrix3;

namespace
{
	float GetDeterminantMatrix2(Matrix3 & matrix)
	{
		return matrix[0][0] * matrix[1][1] -
			matrix[0][1] * matrix[1][0];
	}
	float GetDeterminantMatrix3(Matrix3 & matrix)
	{
		return  matrix[0][0] * matrix[1][1] * matrix[2][2] +
			matrix[0][2] * matrix[1][0] * matrix[2][1] +
			matrix[0][1] * matrix[1][2] * matrix[2][0] -
			matrix[0][2] * matrix[1][1] * matrix[2][0] -
			matrix[0][0] * matrix[1][2] * matrix[2][1] -
			matrix[0][1] * matrix[1][0] * matrix[2][2];
	}
	bool GetMatrix(ifstream & file, Matrix3 & matrix)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (!(file >> matrix[i][j]))
				{
					return false;
				}
			}
		}
		return true;
	}
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: invert.exe <matrix file>\n";
	}

	ifstream matrixFile(argv[1]);

	if (!matrixFile.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	Matrix3 matrix = {
		{ 
			{ 0, 0, 0 },
			{ 0, 0, 0 },
			{ 0, 0, 0 }
		}
	};
	if (!GetMatrix(matrixFile, matrix))
	{
		cout << "Invalid value\n"
			<< "Input File:\n"
			<< "<number> <number> <number>\n"
			<< "<number> <number> <number>\n"
			<< "<number> <number> <number>\n";
		return 1;
	}

	if (GetDeterminantMatrix3(matrix) != 0)
	{

	}
	else
	{
		cout << "Inverse matrix does not exist\n";
	}

	return 0;
}
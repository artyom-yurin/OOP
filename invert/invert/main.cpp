#include <array>
#include <iostream>
#include <fstream>

using namespace std;

typedef array<array <float, 2>, 2> Matrix2;
typedef array<array <float, 3>, 3> Matrix3;

float GetDeterminant(const Matrix2 & matrix)
{
	return matrix[0][0] * matrix[1][1] -
		matrix[0][1] * matrix[1][0];
}

float GetDeterminant(const Matrix3 & matrix)
{
	return  matrix[0][0] * matrix[1][1] * matrix[2][2] +
		matrix[0][2] * matrix[1][0] * matrix[2][1] +
		matrix[0][1] * matrix[1][2] * matrix[2][0] -
		matrix[0][2] * matrix[1][1] * matrix[2][0] -
		matrix[0][0] * matrix[1][2] * matrix[2][1] -
		matrix[0][1] * matrix[1][0] * matrix[2][2];
}

Matrix2 GetMinor(const Matrix3 &matrix, int row, int column)
{
	Matrix2 minor = {
		{
			{ 0, 0 },
			{ 0, 0 }
		}
	};

	int l = 0;
	for (int i = 0; i < 3; ++i)
	{		
		if (i == row)
		{
			continue;
		}
		int k = 0;
		for (int j = 0; j < 3; ++j)
		{
			if (j == column)
			{
				continue;
			}
			minor[l][k] = matrix[i][j];
			++k;
		}
		++l;
	}
	return minor;
}

Matrix3 GetMinorMatrix(const Matrix3 &matrix)
{
	Matrix3 minorMatrix = {
		{
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0}
		}
	};

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			minorMatrix[i][j] = GetDeterminant(GetMinor(matrix, i, j));
		}
	}

	return minorMatrix;
}

void PrintMatrix(const Matrix3 &matrix)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			cout << fixed;
			cout.precision(3);
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
}

void PrintMatrix(const Matrix2 &matrix)
{	
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			cout << fixed;
			cout.precision(3);
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
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

Matrix3 GetMatrixAlgebraicAdditions(const Matrix3 &matrix)
{
	return{ 
		{
			{matrix[0][0], -matrix[0][1], matrix[0][2]},
			{-matrix[1][0], matrix[1][1], -matrix[1][2]},
			{matrix[2][0], -matrix[2][1], matrix[2][2]}
		}
	};
}

Matrix3 GetTransposedMatrixAlgebraicAdditions(const Matrix3 &matrix)
{
	return{
		{
			{matrix[0][0], matrix[1][0], matrix[2][0]},
			{matrix [0][1], matrix[1][1], matrix[2][1]},
			{matrix[0][2], matrix[1][2], matrix[2][2]}
		}
	};
}

Matrix3 MultiplicationScalar(const Matrix3 & matrix, float scalar)
{
	return{ 
		{
			{matrix[0][0] * scalar, matrix[0][1] * scalar, matrix[0][2] * scalar},
			{matrix[1][0] * scalar, matrix[1][1] * scalar, matrix[1][2] * scalar},
			{matrix[2][0] * scalar, matrix[2][1] * scalar, matrix[2][2] * scalar}
		} 
	};
}

Matrix3 InvertMatrix(Matrix3 & matrix)
{
	Matrix3 newMatrix;
	float determinant = 1 / GetDeterminant(matrix);

	newMatrix = GetMinorMatrix(matrix);
	newMatrix = GetMatrixAlgebraicAdditions(newMatrix);
	newMatrix = MultiplicationScalar(newMatrix, determinant);

	return newMatrix;
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

	if (GetDeterminant(matrix) != 0)
	{
		PrintMatrix(InvertMatrix(matrix));
	}
	else
	{
		cout << "Inverse matrix does not exist\n";
	}

	return 0;
}
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
const unsigned MATRIX_DIMENSION3 = 3;
const unsigned MATRIX_DIMENSION2 = 2;

typedef vector<vector <float>> Matrix;

float GetDeterminant2(const Matrix & matrix)
{
	return matrix[0][0] * matrix[1][1] -
		matrix[0][1] * matrix[1][0];
}

float GetDeterminant3(const Matrix & matrix)
{
	return  matrix[0][0] * matrix[1][1] * matrix[2][2] +
		matrix[0][2] * matrix[1][0] * matrix[2][1] +
		matrix[0][1] * matrix[1][2] * matrix[2][0] -
		matrix[0][2] * matrix[1][1] * matrix[2][0] -
		matrix[0][0] * matrix[1][2] * matrix[2][1] -
		matrix[0][1] * matrix[1][0] * matrix[2][2];
}

Matrix GetMinor(const Matrix &matrix, size_t row, size_t column)
{
	Matrix minor (MATRIX_DIMENSION2, vector <float> (MATRIX_DIMENSION2, 0.f));

	size_t l = 0;
	for (size_t i = 0; i < matrix.size(); ++i)
	{		
		if (i == row)
		{
			continue;
		}
		size_t k = 0;
		for (size_t j = 0; j < matrix.size(); ++j)
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

Matrix GetMinorMatrix(const Matrix &matrix)
{
	Matrix minorMatrix (MATRIX_DIMENSION3, vector <float> (MATRIX_DIMENSION3, 0.f));

	for (size_t i = 0; i < minorMatrix.size(); ++i)
	{
		for (size_t j = 0; j < minorMatrix.size(); ++j)
		{
			minorMatrix[i][j] = GetDeterminant2(GetMinor(matrix, i, j));
		}
	}

	return minorMatrix;
}

void PrintMatrix(const Matrix &matrix)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			cout << fixed;
			cout.precision(3);
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
}

bool GetMatrix(ifstream & file, Matrix & matrix)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			if (!(file >> matrix[i][j]))
			{
				return false;
			}
		}
	}
	return true;
}

Matrix GetMatrixAlgebraicAdditions(const Matrix &matrix)
{
	return{ 
		{
			{matrix[0][0], -matrix[0][1], matrix[0][2]},
			{-matrix[1][0], matrix[1][1], -matrix[1][2]},
			{matrix[2][0], -matrix[2][1], matrix[2][2]}
		}
	};
}

Matrix GetTransposedMatrixAlgebraicAdditions(const Matrix &matrix)
{
	return{
		{
			{matrix[0][0], matrix[1][0], matrix[2][0]},
			{matrix [0][1], matrix[1][1], matrix[2][1]},
			{matrix[0][2], matrix[1][2], matrix[2][2]}
		}
	};
}

Matrix MultiplicationScalar(const Matrix & matrix, float scalar)
{
	return{ 
		{
			{matrix[0][0] * scalar, matrix[0][1] * scalar, matrix[0][2] * scalar},
			{matrix[1][0] * scalar, matrix[1][1] * scalar, matrix[1][2] * scalar},
			{matrix[2][0] * scalar, matrix[2][1] * scalar, matrix[2][2] * scalar}
		} 
	};
}

Matrix InvertMatrix(Matrix & matrix)
{
	Matrix newMatrix(MATRIX_DIMENSION3, vector <float> (MATRIX_DIMENSION3, 0.f));
	float determinant = 1 / GetDeterminant3(matrix);

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
		return 1;
	}

	ifstream matrixFile(argv[1]);

	if (!matrixFile.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	Matrix matrix (MATRIX_DIMENSION3, vector <float> (MATRIX_DIMENSION3, 0.f));
	if (!GetMatrix(matrixFile, matrix))
	{
		cout << "Invalid value\n"
			<< "Input File:\n"
			<< "<number> <number> <number>\n"
			<< "<number> <number> <number>\n"
			<< "<number> <number> <number>\n";
		return 1;
	}

	if (GetDeterminant3(matrix) != 0)
	{
		PrintMatrix(InvertMatrix(matrix));
	}
	else
	{
		cout << "Inverse matrix does not exist\n";
	}

	return 0;
}
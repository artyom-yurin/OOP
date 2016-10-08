#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
const unsigned MATRIX_DIMENSION3 = 3;
const unsigned MATRIX_DIMENSION2 = 2;

typedef vector<vector <float>> Matrix;

float GetDeterminant2Matrix(const Matrix & matrix)
{
	return matrix[0][0] * matrix[1][1] -
		matrix[0][1] * matrix[1][0];
}

float GetDeterminant3Matrix(const Matrix & matrix)
{
	return  matrix[0][0] * matrix[1][1] * matrix[2][2] +
		matrix[0][2] * matrix[1][0] * matrix[2][1] +
		matrix[0][1] * matrix[1][2] * matrix[2][0] -
		matrix[0][2] * matrix[1][1] * matrix[2][0] -
		matrix[0][0] * matrix[1][2] * matrix[2][1] -
		matrix[0][1] * matrix[1][0] * matrix[2][2];
}

//float GetDeterminant(const Matrix & matrix)
//{
//	float determinant = 0.f;
//	size_t size = matrix.size();
//	Matrix currentMatrix(size, vector <float>(size, 0.f));
//	currentMatrix = matrix;
//
//	float degree = 0;
//	for (size_t i = 0; i < size - 1; ++i)
//	{
//		size_t t = 1;
//		while (currentMatrix[i][i] == 0)
//		{
//			for (size_t j = 0; j < size; ++j)
//			{
//				currentMatrix[i][j] = determinant;
//				currentMatrix[i][j] = currentMatrix[i + t][j];
//				currentMatrix[i + t][j] = determinant;
//			}
//			degree++;
//			t++;
//		}
//
//		for (size_t k = i + 1; k < size; ++k)
//		{
//			determinant = currentMatrix[k][i] / currentMatrix[i][i];
//			for (size_t j = 0; j < size; j++)
//				currentMatrix[k][j] -= currentMatrix[i][j] * determinant;
//		}
//	}
//
//	determinant = pow(-1.f, degree);
//	for (size_t i = 0; i < size; ++i)
//		determinant *= currentMatrix[i][i];
//
//	return determinant;
//}

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

Matrix GetMatrixMinor(const Matrix &matrix)
{
	Matrix minorMatrix (MATRIX_DIMENSION3, vector <float> (MATRIX_DIMENSION3, 0.f));

	for (size_t i = 0; i < minorMatrix.size(); ++i)
	{
		for (size_t j = 0; j < minorMatrix.size(); ++j)
		{
			minorMatrix[i][j] = GetDeterminant2Matrix(GetMinor(matrix, i, j));
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
			cout << fixed
				<< setprecision(3)
				<< matrix[i][j] << " ";
		}
		cout << endl;
	}
}

bool CanReadMatrixFromFile(ifstream & file, Matrix & matrix)
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

Matrix GetAlgebraicAdditionsMatrix(const Matrix &matrix)
{
	Matrix newMatrix(MATRIX_DIMENSION3, vector <float>(MATRIX_DIMENSION3, 0.f));

	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			newMatrix[i][j] = matrix[i][j];
			if (((matrix.size() * i) + (j + 1)) % 2 == 0)
			{
				newMatrix[i][j] *= -1;
			}
		}
	}

	return newMatrix;
}

Matrix GetAlgebraicAdditionsMatrixTransposed(const Matrix &matrix)
{
	Matrix newMatrix(MATRIX_DIMENSION3, vector <float>(MATRIX_DIMENSION3, 0.f));

	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			newMatrix[i][j] = matrix[j][i];
		}
	}

	return newMatrix;
}

Matrix MultiplicationScalarOnMatrix(const Matrix & matrix, float scalar)
{
	Matrix newMatrix(MATRIX_DIMENSION3, vector <float>(MATRIX_DIMENSION3, 0.f));

	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			newMatrix[i][j] = matrix[i][j] * scalar;
		}
	}

	return newMatrix;
}

void InvertMatrix(const Matrix & matrix)
{
	if (GetDeterminant3Matrix(matrix) != 0)
	{
		Matrix newMatrix(MATRIX_DIMENSION3, vector <float>(MATRIX_DIMENSION3, 0.f));
		float determinant = 1 / GetDeterminant3Matrix(matrix);

		newMatrix = GetMatrixMinor(matrix);
		newMatrix = GetAlgebraicAdditionsMatrix(newMatrix);
		newMatrix = GetAlgebraicAdditionsMatrixTransposed(newMatrix);
		newMatrix = MultiplicationScalarOnMatrix(newMatrix, determinant);

		PrintMatrix(newMatrix);
	}
	else
	{
		cout << "Inverse matrix does not exist" << endl;
	}
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count" << endl
			<< "Usage: invert.exe <matrix file>" << endl;
		return 1;
	}

	ifstream matrixFile(argv[1]);

	if (!matrixFile.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading" << endl;
		return 1;
	}

	Matrix matrix (MATRIX_DIMENSION3, vector <float> (MATRIX_DIMENSION3, 0.f));
	if (!CanReadMatrixFromFile(matrixFile, matrix))
	{
		cout << "Invalid value" << endl
			<< "Input File:" << endl
			<< "<number> <number> <number>" << endl
			<< "<number> <number> <number>" << endl
			<< "<number> <number> <number>" << endl;
		return 1;
	}

	InvertMatrix(matrix);

	return 0;
}
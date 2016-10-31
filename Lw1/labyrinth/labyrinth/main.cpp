#include <iostream>
#include <fstream>
#include <array>
#include <string>

const int MAX_WIDTH_LABYRINTH_PROTECTION = 102;
const int MAX_HEIGHT_LABYRINTH_PROTECTION = 102;
const int FINISH_POINT_NUMBER = 3;
const int WAY_POINT_NUMBER = 2;
const int START_POINT_NUMBER = 1;
const int WALL_POINT_NUMBER = -1;
const int MAX_WIDTH_LABYRINTH = 100;
const int MAX_HEIGHT_LABYRINTH = 100;

using namespace std;

typedef array <array <int, MAX_WIDTH_LABYRINTH_PROTECTION>, MAX_HEIGHT_LABYRINTH_PROTECTION> Labyrinth;

struct Vector2u
{
	size_t x = 0;
	size_t y = 0;
};

void PrintLabyrinth(ofstream & output, const Labyrinth & labyrinth, const Vector2u & size)
{
	for (size_t i = 1; i <= size.y; ++i)
	{
		for (size_t j = 1; j <= size.x; ++j)
		{
			switch (labyrinth[i][j])
			{
				case WALL_POINT_NUMBER:
				{
					output << '#';
					break;
				}
				case 0:
				{
					output << ' ';
					break;
				}
				case START_POINT_NUMBER:
				{
					output << 'A';
					break;
				}
				case WAY_POINT_NUMBER:
				{
					output << '.';
					break;
				}
				case FINISH_POINT_NUMBER:
				{
					output << 'B';
					break;
				}
			}
		}
		output << "\n";
	}
}

void InitLabyrinth(Labyrinth & labyrinth)
{
	for (size_t i = 1; i < MAX_HEIGHT_LABYRINTH_PROTECTION; ++i)
	{
		for (size_t j = 1; j < MAX_WIDTH_LABYRINTH; ++j)
		{
			labyrinth[i][j] = 0;
		}
	}
	for (size_t j = 0; j < MAX_WIDTH_LABYRINTH; ++j)
	{
		labyrinth[0][j] = WALL_POINT_NUMBER;
		labyrinth[101][j] = WALL_POINT_NUMBER;
	}
	for (size_t i = 0; i < MAX_HEIGHT_LABYRINTH_PROTECTION; ++i)
	{
		labyrinth[i][0] = WALL_POINT_NUMBER;
		labyrinth[i][101] = WALL_POINT_NUMBER;
	}
}

bool StartWave(Labyrinth & labyrinth, const Vector2u & size, const Vector2u & finalPoint)
{
	int currentNumber = 1;
	bool isIteration = false;
	while ((labyrinth[finalPoint.y][finalPoint.x] == 0) && (!isIteration))
	{
		isIteration = true;
		for (size_t i = 1; i <= size.y; ++i)
		{
			for (size_t j = 1; j <= size.x; ++j)
			{
				if (labyrinth[i][j] == currentNumber)
				{
					if (labyrinth[i + 1][j] == 0)
					{
						labyrinth[i + 1][j] = currentNumber + 1;
						isIteration = false;
					}
					if (labyrinth[i - 1][j] == 0)
					{
						labyrinth[i - 1][j] = currentNumber + 1;
						isIteration = false;
					}
					if (labyrinth[i][j + 1] == 0)
					{
						labyrinth[i][j + 1] = currentNumber + 1;
						isIteration = false;
					}
					if (labyrinth[i][j - 1] == 0)
					{
						labyrinth[i][j - 1] = currentNumber + 1;
						isIteration = false;
					}
				}
			}
		}
		++currentNumber;
	}

	if (isIteration)
	{
		return false;
	}

	return true;
}

void FindWay(const Labyrinth & currentLabyrinth, Labyrinth & labyrinth, Vector2u finishPoint)
{
	size_t i = finishPoint.y;
	size_t j = finishPoint.x;
	size_t currentNumber = currentLabyrinth[i][j];
	while (currentNumber > 1)
	{
		if (currentLabyrinth[i + 1][j] == currentNumber - 1)
		{
			labyrinth[i + 1][j] = WAY_POINT_NUMBER;
			++i;
		}
		else if (currentLabyrinth[i - 1][j] == currentNumber - 1)
		{
			labyrinth[i - 1][j] = WAY_POINT_NUMBER;
			--i;
		}
		else if (currentLabyrinth[i][j + 1] == currentNumber - 1)
		{
			labyrinth[i][j + 1] = WAY_POINT_NUMBER;
			++j;
		}
		else if (currentLabyrinth[i][j - 1] == currentNumber - 1)
		{
			labyrinth[i][j - 1] = WAY_POINT_NUMBER;
			--j;
		}
		--currentNumber;
	}
	labyrinth[i][j] = START_POINT_NUMBER;
	labyrinth[finishPoint.y][finishPoint.x] = FINISH_POINT_NUMBER;
}

bool HasWayFound(Labyrinth & labyrinth, const Vector2u & labyrinthSize, Vector2u finishPoint)
{
	Labyrinth currentLabyrinth = labyrinth;
	if (!StartWave(currentLabyrinth, labyrinthSize, finishPoint))
	{
		return false;
	}
	FindWay(currentLabyrinth, labyrinth, finishPoint);
	return true;
}

bool CanReadLabyrinthFromFile(ifstream & input, Labyrinth & labyrinth, Vector2u & size, Vector2u & finishPoint)
{
	string line;
	size_t i = 0;
	int countPoint = 0;
	while (getline(input, line))
	{
		if (i > MAX_HEIGHT_LABYRINTH)
		{
			return false;
		}
		if (size.x < line.size())
		{
			if (line.size() > MAX_WIDTH_LABYRINTH)
			{
				return false;
			}
			size.x = line.size();
		}
		for (size_t j = 0; j < line.size(); ++j)
		{
			switch (line[j])
			{
			    case '#':
				{
					labyrinth[i + 1][j + 1] = WALL_POINT_NUMBER;
					break;
				}
				case ' ':
				{
					labyrinth[i + 1][j + 1] = 0;
					break;
				}
				case 'A':
				{
					labyrinth[i + 1][j + 1] = 1;
					if (countPoint < 2)
					{
						++countPoint;
					}
					else
					{
						return false;
					}
					break;
				}
				case 'B':
				{
					labyrinth[i + 1][j + 1] = 0;
					finishPoint.x = j + 1;
					finishPoint.y = i + 1;
					if (countPoint < 2)
					{
						++countPoint;
					}
					else
					{
						return false;
					}
					break;
				}
				default:
				{ 
					return false;
				}
			}		
		}
		++i;
	}
	if (countPoint != 2)
	{
		return false;
	}
	size.y = i;

	return true;
}

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: labyrinth.exe <input file> <output file>\n";
		return 1;
	}

	ifstream input(argv[1]);

	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for writing\n";
		return 1;
	}

	ofstream output(argv[2]);

	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}

	Labyrinth labyrinth;
	InitLabyrinth(labyrinth);
	Vector2u finishPoint;
	Vector2u labyrinthSize;
	
	if (!CanReadLabyrinthFromFile(input, labyrinth, labyrinthSize, finishPoint))
	{
		cout << "Failed to read labyrinth\n"
			<< "Labyrinth have not 1 start point and 1 finish point\n"
			<< "or Labyrinth's size invalid\n";
		return 1;
	}

	if (!HasWayFound(labyrinth, labyrinthSize, finishPoint))
	{
		cout << "Labyrinth has no access\n";
		return 1;
	}

	PrintLabyrinth(output, labyrinth, labyrinthSize);

	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}
	return 0;
}
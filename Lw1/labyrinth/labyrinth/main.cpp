#include <iostream>
#include <fstream>
#include <array>
#include <string>

const int MAX_WIDTH_LABYRINTH = 102;
const int MAX_HEIGHT_LABYRINTH = 102;

using namespace std;

typedef array <array <int, MAX_WIDTH_LABYRINTH>, MAX_HEIGHT_LABYRINTH> Labyrinth;

struct Vector2u
{
	size_t x = 0;
	size_t y = 0;
};

struct Points
{
	Vector2u startPoint;
	Vector2u finishPoint;
};

void PrintLabyrinth(ofstream & output, const Labyrinth & labyrinth, const Vector2u & size)
{
	for (size_t i = 1; i <= size.y; ++i)
	{
		for (size_t j = 1; j <= size.x; ++j)
		{
			switch (labyrinth[i][j])
			{
				case -1:
				{
					output << '#';
					break;
				}
				case 0:
				{
					output << ' ';
					break;
				}
				case 1:
				{
					output << 'A';
					break;
				}
				case 2:
				{
					output << '.';
					break;
				}
				case 3:
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
	for (size_t i = 1; i < MAX_HEIGHT_LABYRINTH; ++i)
	{
		for (size_t j = 1; j < MAX_WIDTH_LABYRINTH; ++j)
		{
			labyrinth[i][j] = 0;
		}
	}
	for (size_t j = 0; j < MAX_WIDTH_LABYRINTH; ++j)
	{
		labyrinth[0][j] = -1;
		labyrinth[101][j] = -1;
	}
	for (size_t i = 0; i < MAX_HEIGHT_LABYRINTH; ++i)
	{
		labyrinth[i][0] = -1;
		labyrinth[i][101] = -1;
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

void FindWay(const Labyrinth & currentLabyrinth, Labyrinth & labyrinth, const Points & points)
{
	size_t i = points.finishPoint.y;
	size_t j = points.finishPoint.x;
	size_t currentNumber = currentLabyrinth[i][j];
	while (currentNumber > 1)
	{
		if (currentLabyrinth[i + 1][j] == currentNumber - 1)
		{
			labyrinth[i + 1][j] = 2;
			++i;
		}
		else if (currentLabyrinth[i - 1][j] == currentNumber - 1)
		{
			labyrinth[i - 1][j] = 2;
			--i;
		}
		else if (currentLabyrinth[i][j + 1] == currentNumber - 1)
		{
			labyrinth[i][j + 1] = 2;
			++j;
		}
		else if (currentLabyrinth[i][j - 1] == currentNumber - 1)
		{
			labyrinth[i][j - 1] = 2;
			--j;
		}
		--currentNumber;
	}
	labyrinth[i][j] = 1;
	labyrinth[points.finishPoint.y][points.finishPoint.x] = 3;
}

bool FindWayLabyrinth(Labyrinth & labyrinth, const Vector2u & labyrinthSize, const Points points)
{
	Labyrinth currentLabyrinth = labyrinth;
	if (!StartWave(currentLabyrinth, labyrinthSize, points.finishPoint))
	{
		return false;
	}
	FindWay(currentLabyrinth, labyrinth, points);
	return true;
}

bool CanReadLabyrinthFromFile(ifstream & input, Labyrinth & labyrinth, Vector2u & size, Points & points)
{
	string line;
	size_t i = 0;
	int countPoint = 0;
	while (getline(input, line))
	{
		if (i > 100)
		{
			return false;
		}
		if (size.x < line.size())
		{
			if (line.size() > 100)
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
					labyrinth[i + 1][j + 1] = -1;
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
					points.startPoint.x = j + 1;
					points.startPoint.y = i + 1;
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
					points.finishPoint.x = j + 1;
					points.finishPoint.y = i + 1;
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
	Points points;
	Vector2u labyrinthSize;
	
	if (!CanReadLabyrinthFromFile(input, labyrinth, labyrinthSize, points))
	{
		cout << "Failed to read labyrinth\n"
			<< "Labyrinth have not 1 start point and 1 finish point\n"
			<< "or Labyrinth's size invalid\n";
		return 1;
	}

	if (!FindWayLabyrinth(labyrinth, labyrinthSize, points))
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
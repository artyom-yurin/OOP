#include <iostream>
#include <fstream>
#include <array>
#include <string>

const int MAX_WIDTH_LABYRINTH = 102;
const int MAX_HEIGHT_LABYRINTH = 102;

using namespace std;
typedef array <array <char, MAX_WIDTH_LABYRINTH>, MAX_HEIGHT_LABYRINTH> LabyrinthChar;
typedef array <array <int, MAX_WIDTH_LABYRINTH>, MAX_HEIGHT_LABYRINTH> LabyrinthInt;

struct Size
{
	size_t width = 0;
	size_t height = 0;
};

void PrintLabyrinth(ofstream & output, LabyrinthChar & labyrinth, const Size & size)
{
	for (size_t i = 0; i < size.height; ++i)
	{
		for (size_t j = 0; j < size.width; ++j)
		{
			output << labyrinth[i][j];
		}
		output << "\n";
	}
}

void InitLabyrinth(LabyrinthInt & labyrinth)
{
	for (size_t i = 0; i < MAX_HEIGHT_LABYRINTH; ++i)
	{
		for (size_t j = 0; j < MAX_WIDTH_LABYRINTH; ++j)
		{
			labyrinth[i][j] = -1;
		}
	}
}

void ConvertLabyrintIntToChar(LabyrinthChar & labyrinth, LabyrinthInt & labyrinthInt, Size & size)
{
	for (size_t i = 0; i < size.height; ++i)
	{
		for (size_t j = 0; j < size.width; ++j)
		{
			switch (labyrinth[i][j])
			{
				case '#': 
					labyrinth[i + 1][j + 1] = -1;
					break;
				case ' ':
					labyrinth[i + 1][j + 1] = 0;
					break;
			}
		}
	}
}

bool FindWayLabyrinth(LabyrinthChar & labyrinth, Size & labyrinthSize)
{
	LabyrinthInt  labyrinthInt;
	InitLabyrinth(labyrinthInt);
	ConvertLabyrintIntToChar(labyrinth, labyrinthInt, labyrinthSize);


	return true;
}

bool CanReadLabyrinthFromFile(ifstream & input, LabyrinthChar & labyrinth, Size & size)
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
		if (size.width < line.size())
		{
			size.width = line.size();
			if (size.width > 100)
			{
				return false;
			}
		}
		for (size_t j = 0; j < size.width; ++j)
		{
			if ((line[j] == 'A') || (line[j] == 'B') || (line[j] == '#') || (line[j] == ' '))
			{
				labyrinth[i][j] = line[j];
				if ((labyrinth[i][j] == 'A') || (labyrinth[i][j] == 'B'))
				{
					++countPoint;
				}
			} 
			else
			{
				return false;
			}
			
		}
		++i;
	}
	size.height = i;

	if (countPoint != 2)
	{
		return false;
	}

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

	LabyrinthChar labyrinthCh;
	Size labyrinthSize;
	
	if (!CanReadLabyrinthFromFile(input, labyrinthCh, labyrinthSize))
	{
		cout << "Failed to read labyrinth\n"
			<< "Labyrinth have not 1 start point and 1 finish point\n"
			<< "or Labyrinth's size invalid\n";
		return 1;
	}

	FindWayLabyrinth(labyrinthCh, labyrinthSize);

	PrintLabyrinth(output, labyrinthCh, labyrinthSize);

	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}
	return 0;
}
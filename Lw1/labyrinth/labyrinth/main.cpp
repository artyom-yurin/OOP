#include <iostream>
#include <fstream>
#include <array>
#include <string>

const int MAX_WIDTH_LABYRINTH = 100;
const int MAX_HEIGHT_LABYRINTH = 100;

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

bool CanReadLabyrinthFromFile(ifstream & input, LabyrinthChar & labyrinth, Size & size)
{
	string line;
	size_t i = 0;
	int countPoint = 0;
	while (getline(input, line))
	{
		if (size.width < line.size())
		{
			size.width = line.size();
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
	LabyrinthInt  labyrinthInt;
	Size labyrinthSize;
	
	if (!CanReadLabyrinthFromFile(input, labyrinthCh, labyrinthSize))
	{
		cout << "Failed to read labyrinth\n"
			<< "Labyrinth have not 1 start point and 1 finish point\n";
		return 1;
	}

	PrintLabyrinth(output, labyrinthCh, labyrinthSize);

	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}
	return 0;
}
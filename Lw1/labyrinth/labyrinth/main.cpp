#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count" << endl
			<< "Usage: labyrinth.exe <input file> <output file>" << endl;
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

	//TODO: Labyrinth

	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}
	return 0;
}
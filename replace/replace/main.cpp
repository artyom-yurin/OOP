#include <string>
#include <iostream>
#include <fstream>

using namespace std;

namespace
{
	auto FindAndReplace(const std::string & inputString, const std::string & searchString, const std::string & replaceString)
	{
		std::string newString = inputString;
		auto positionString = newString.find(searchString, 0);

		while (positionString != string::npos)
		{
			newString.replace(positionString, searchString.size(), replaceString);
			positionString = newString.find(searchString, positionString + replaceString.size());
		}
		
		return newString;
	}
}

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	ifstream input(argv[1]);

	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	string searchString = argv[3];

	if (searchString == "")
	{
		cout << "Search string can not be empty\n";
		return 1;
	}

	string replaceString = argv[4];

	ofstream output(argv[2]);

	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}

	string currentString = "";

	while (getline(input, currentString))
	{
		currentString = FindAndReplace(currentString, searchString, replaceString);
		if (!(output << currentString << "\n"))
		{
			cout << "Failed to save data on disk\n";
			return 1;
		}
	}

	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}

	return 0;
}
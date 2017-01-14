#include "stdafx.h"
#include "ConsoleMenu.h"
#include <iostream>
#include <sstream>

int main()
{
	CConsoleMenu menu;
	while (!std::cin.eof())
	{
		std::stringstream buffer;
		std::string command;
		std::cout << "Enter command: ";
		getline(std::cin, command);
		buffer << command;
		std::cout << "\n";
		menu.RunCommand(buffer, std::cout);
	}
	return 0;
}
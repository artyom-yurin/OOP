#include "stdafx.h"
#include "..\Car\Car.h"
#include "CarModel_functions.h"

int main()
{
	std::cout << "Welcome to the car emulator\n";
	while (true)
	{
		std::string command = GetCommand(std::cin);
		if (command == "info")
		{
			//TODO: get info
		}
		else if (command == "engineon")
		{
			//TODO: turn on engine
		}
		else if (command == "engineoff")
		{
			//TODO: turn off engine
		}
		else if (command == "setgear")
		{
			//TODO: set gear
		}
		else if (command == "setspeed")
		{
			//TODO: set speed
		}
		else if (command == "exit")
		{
			std::cout << "Good bye\n";
			return 0;
		}
		else
		{
			std::cout << "Unknown command.\n";
		}
	}
}


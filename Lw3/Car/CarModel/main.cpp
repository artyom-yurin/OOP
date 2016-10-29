#include "stdafx.h"
#include "..\Car\Car.h"
#include "CarModel_functions.h"

int main()
{
	CCar car;
	std::cout << "Welcome to the car emulator\n";
	while (true)
	{
		std::cout << "\nEnter command: ";
		std::string command = GetCommand(std::cin);
		if (command == "info")
		{
			std::cout << "Answer:\n";
			GetInfo(std::cout, car);
		}
		else if (command == "engineon")
		{
			std::cout << "Answer:\n";
			EngineOn(std::cout, car);
		}
		else if (command == "engineoff")
		{
			std::cout << "Answer:\n";
			EngineOff(std::cout, car);
		}
		else if (command == "setgear")
		{
			int value = 0;
			std::cout << "Enter value: ";
			if (GetValue(std::cin, value))
			{
				std::cout << "Answer:\n";

				if (SetGear(car, value))
				{
					std::cout << "	Gear " << value << " succesfuly installed\n";
				}
				else if (!car.GetEngineStatus())
				{
					std::cout << "	Gear can not be installed\n"
						<< "	Engine is off\n";
				}
				else if ((car.GetDirection() == -1) && (value > 0) || ((car.GetDirection() == 1) && (value < 0)))
				{
					std::cout << "	Gear can not be installed\n"
						<< "	Car moves in opposite direction\n";
				}
				else
				{
					std::cout << "	Wrong speed\n";
				}
			}
			else
			{
				std::cout << "Answer:\n"
					<< "Invalid value\n";
			}
			
		}
		else if (command == "setspeed")
		{

			std::cout << "Answer:\n";
			//TODO: set speed
		}
		else if (command == "exit")
		{
			std::cout << "Answer:\n";
			std::cout << "	Good bye\n";
			return 0;
		}
		else
		{
			std::cout << "	Unknown command.\n";
		}
	}
}


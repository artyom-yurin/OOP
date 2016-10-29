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
			std::cout << "Enter gear: ";
			if (GetValue(std::cin, value))
			{
				std::cout << "Answer:\n";
				if ((value >= -1) && (value <= 5))
				{
					if (SetGear(car, value))
					{
						std::cout << "	Gear " << value << " succesfuly installed\n";
					}
					else if (!car.IsEngineOn())
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
						std::cout << "	Gear can not be installed\n"
							<< "	Wrong speed\n";
					}
				}
				else
				{
					std::cout << "	Gear must be -1 to 5\n";
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
			int value = 0;
			std::cout << "Enter speed: ";
			if (GetValue(std::cin, value))
			{
				std::cout << "Answer:\n";
				if ((value >= 0) && (value <= 150))
				{
					if (SetSpeed(car, value))
					{
						std::cout << "	Speed " << value << " succesfuly installed\n";
					}
					else if (!car.IsEngineOn())
					{
						std::cout << "	Speed can not be installed\n"
							<< "	Engine is off\n";
					}
					else
					{
						std::cout << "	Speed can not be installed\n"
							<< "	Wrong gear\n";
					}
				}
				else
				{
					std::cout << "	Speed must be 0 to 20 on R gear\n"
						<< "	Speed must be 0 on N gear\n"
						<< "	Speed must be 0 to 30 on 1 gear\n"
						<< "	Speed must be 20 to 50 on 2 gear\n"
						<< "	Speed must be 30 to 60 on 3 gear\n"
						<< "	Speed must be 40 to 90 on 4 gear\n"
						<< "	Speed must be 50 to 150 on 5 gear\n";
				}
			}
			else
			{
				std::cout << "Answer:\n"
					<< "Invalid value\n";
			}
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


#include "stdafx.h"
#include "..\Car\Car.h"
#include "CarModel_functions.h"

int main()
{
	CCar car;
	std::cout << "Welcome to the car emulator\n";
	while (!std::cin.eof())
	{
		std::cout << "\nEnter command: ";
		std::string command;
		std::getline(std::cin, command);
		std::stringstream buffer;
		buffer << command;
		buffer >> command;
		if (command == "Info")
		{
			std::cout << "Answer:\n";
			GetInfo(std::cout, car);
		}
		else if (command == "EngineOn")
		{
			std::cout << "Answer:\n";
			EngineOn(std::cout, car);
		}
		else if (command == "EngineOff")
		{
			std::cout << "Answer:\n";
			EngineOff(std::cout, car);
		}
		else if (command == "SetGear")
		{
			int value = 0;
			std::cout << "Answer:\n";
			if (buffer >> value)
			{
				if ((value >= -1) && (value <= 5))
				{
					if (SetGear(car, value))
					{
						std::cout << "	Gear " << value << " succesfuly set\n";
					}
					else if (!car.IsEngineOn())
					{
						std::cout << "	Gear can not be set\n"
							<< "	Engine is off\n";
					}
					else if ((car.GetDirection() == Direction::reverse) && (value > 0) || ((car.GetDirection() == Direction::forward) && (value < 0)))
					{
						std::cout << "	Gear can not be set\n"
							<< "	Car moves in opposite direction\n";
					}
					else
					{
						std::cout << "	Gear can not be set\n"
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
				std::cout << "	Invalid value\n"
					<< "	Use command: SetGear <value>\n";
			}
		}
		else if (command == "SetSpeed")
		{
			int value = 0;
			std::cout << "Answer:\n";
			if (buffer >> value)
			{
				if ((value >= 0) && (value <= 150))
				{
					if (SetSpeed(car, value))
					{
						std::cout << "	Speed " << value << " succesfuly set\n";
					}
					else if (!car.IsEngineOn())
					{
						std::cout << "	Speed can not be set\n"
							<< "	Engine is off\n";
					}
					else
					{
						std::cout << "	Speed can not be set\n"
							<< "	Wrong gear\n"
							<< "	Speed must be 0 to 20 on R gear\n"
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
					std::cout << "	Value must be 0 to 150\n";
				}
			}
			else
			{
				std::cout << "	Invalid value\n"
					<< "	Use command: SetSpeed <value>\n";
			}
		}
		else if (std::cin.eof())
		{
			std::cout << "Answer:\n";
			std::cout << "	Good bye\n";
		}
		else
		{
			std::cout << "	Unknown command.\n"
				<< "	Use commands: Info\n"
				<< "	SetGear <value>\n"
				<< "	SetSpeed <value>\n"
				<< "	EngineOn\n"
				<< "	EngineOff\n";
		}
	}
	return 0;
}


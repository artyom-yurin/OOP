#include "stdafx.h"
#include "CarModel_functions.h"

void GetInfo(std::ostream & output, CCar & car)
{
	output << "	Car's info\n";
	output << "	Engine status: ";
	if (car.GetEngineStatus())
	{
		output << "ON\n";
	}
	else
	{
		output << "OFF\n";
	}
	output << "	Current gear: ";
	int gear = car.GetGear();
	if (gear == -1)
	{
		output << "R\n";
	}
	else if (gear == 0)
	{
		output << "N\n";
	}
	else
	{
		output << gear << "\n";
	}
	output << "	Current speed: " << car.GetSpeed() << "\n";
	output << "	Current Direction: "; 
	int direction = car.GetDirection();
	if (direction == -1)
	{
		output << "reverse\n";
	}
	else if (direction == 1)
	{
		output << "forward\n";
	}
	else
	{
		output << "stand\n";
	}
}

void EngineOn(std::ostream & output, CCar & car)
{
	if (car.TurnOnEngine())
	{
		output << "	Engine have turned on\n";
	}
	else
	{
		output << "	Engine has been already turned on\n";
	}
}

void EngineOff(std::ostream & output, CCar & car)
{
	if (car.TurnOffEngine())
	{
		output << "	Engine have turned off\n";
	}
	else if (!car.GetEngineStatus())
	{
		output << "	Engine has been already turned off\n";
	}
	else if (car.GetGear() != 0)
	{
		output << "	Gear must be neutral\n";
	}
	else
	{
		output << "	Car must stand\n";
	}
}

bool SetGear(CCar & car, int value)
{
	return car.SetGear(value);
}

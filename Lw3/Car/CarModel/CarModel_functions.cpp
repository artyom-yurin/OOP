#include "stdafx.h"
#include "CarModel_functions.h"

void GetInfo(std::ostream & output, CCar & car)
{
	output << "Car's info\n";
	output << "Engine status: ";
	if (car.GetEngineStatus())
	{
		output << "ON\n";
	}
	else
	{
		output << "OFF\n";
	}
	output << "Current gear: ";
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
	output << "Current speed: " << car.GetSpeed() << "\n";
	output << "Current Direction: "; 
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

#include "stdafx.h"
#include "CarModel_functions.h"

std::string GetDirection(CCar & car)
{
	switch (car.GetDirection())
	{
	case Direction::reverse: return "reverse";
	case Direction::forward: return "forward";
	case Direction::stand: return "stand";
	default: return "";
	}
}

void GetInfo(std::ostream & output, CCar & car)
{
	output << "	Car's info\n";
	output << "	Engine status: ";
	if (car.IsEngineOn())
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
	output << "	Current Direction: " << GetDirection(car) << "\n";
}

void EngineOn(std::ostream & output, CCar & car)
{
	if (car.TurnOnEngine())
	{
		output << "	Engine has been turned on\n";
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
		output << "	Engine has been turned off\n";
	}
	else if (!car.IsEngineOn())
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

bool SetSpeed(CCar & car, int value)
{
	return car.SetSpeed(value);
}

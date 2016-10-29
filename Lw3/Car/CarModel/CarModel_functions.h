#pragma once

#include "..\Car\Car.h"

inline std::string GetCommand(std::istream & input)
{
	std::string command = "";
	getline(input, command);
	std::transform(command.begin(), command.end(), command.begin(), ::tolower);
	return command;
}

void GetInfo(std::ostream & output, CCar & car);

void EngineOn(std::ostream & output, CCar & car);

void EngineOff(std::ostream & output, CCar & car);
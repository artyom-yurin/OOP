#pragma once

#include "..\Car\Car.h"

inline std::string GetCommand(std::istream & input)
{
	std::string command = "";
	getline(input, command);
	std::transform(command.begin(), command.end(), command.begin(), ::tolower);
	return command;
}

inline bool IsNumber(std::string & str)
{
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (str[0] != '-')
		{
			if (!isdigit(str[i])) {
				return false;
			}
		}		
	}
	return true;
}

inline bool GetValue(std::istream & input, int & value)
{
	std::string result;
	getline(input, result);
	if (!IsNumber(result))
	{
		return false;
	}
	value = atoi(result.c_str());
	return true;
}

void GetInfo(std::ostream & output, CCar & car);

void EngineOn(std::ostream & output, CCar & car);

void EngineOff(std::ostream & output, CCar & car);

bool SetGear(CCar & car, int value);
#pragma once

inline std::string GetCommand(std::istream & input)
{
	std::string command = "";
	getline(input, command);
	std::transform(command.begin(), command.end(), command.begin(), ::tolower);
	return command;
}
#pragma once
#include "Calc.h"

class CConsoleMenu
{
public:
	CConsoleMenu() = default;

	~CConsoleMenu() = default;
	
	void RunCommand(std::istream & stream, std::ostream & outputs);
private:
	CCalc calc;
};


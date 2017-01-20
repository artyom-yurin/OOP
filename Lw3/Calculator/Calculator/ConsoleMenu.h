#pragma once
#include "Calc.h"

class CConsoleMenu
{
public:
	CConsoleMenu() = default;

	~CConsoleMenu() = default;
	
	void RunCommand(std::istream & stream, std::ostream & output);
private:
	void CommandPrintvars(std::ostream & output);
	void CommandPrintfns(std::ostream & output);
	void CommandPrint(std::istream & stream, std::ostream & output);
	void CommandVar(std::istream & stream, std::ostream & output);
	void CommandLet(std::istream & stream, std::ostream & output);
	void CommandFn(std::istream & stream, std::ostream & output);

	CCalc calc;
};


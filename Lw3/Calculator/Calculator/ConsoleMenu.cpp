#include "stdafx.h"
#include "ConsoleMenu.h"
#include <sstream>
#include <iostream>

const std::string INDENTIFER_PATTERN = "([A-Za-z]\\w*)";
const std::string DOUBLE_NUMBER_PATERN = "(\\d+(\\.\\d+)?)";
const std::string SPACE_PATTERN = "( )*";
const std::string SIGN_PATERN = "(\\+|\\*|/|-)";
const std::string LET_PATTERN = SPACE_PATTERN + INDENTIFER_PATTERN + SPACE_PATTERN + "=" + SPACE_PATTERN + "((" + INDENTIFER_PATTERN + ")|(" + DOUBLE_NUMBER_PATERN + "))" + SPACE_PATTERN;
const std::string FN_PATTERN = SPACE_PATTERN + INDENTIFER_PATTERN + SPACE_PATTERN + "=" + SPACE_PATTERN + INDENTIFER_PATTERN + SPACE_PATTERN + "(" + SIGN_PATERN + SPACE_PATTERN + INDENTIFER_PATTERN + SPACE_PATTERN + ")?";

void CConsoleMenu::RunCommand(std::istream & stream, std::ostream & output)
{
	std::string command;
	stream >> command;
	if (command == "var")
	{
		CommandVar(stream, output);
	}
	else if (command == "let")
	{
		CommandLet(stream, output);
	}
	else if (command == "fn")
	{
		CommandFn(stream, output);
	}
	else if (command == "print")
	{
		CommandPrint(stream, output);
	}
	else if (command == "printvars")
	{
		CommandPrintvars(output);
	}
	else if (command == "printfns")
	{
		CommandPrintfns(output);
	}
	else if (command == "help")
	{
		output << "Using:\n"
			<< "var <identifier>\n"
			<< "let <identifier>=<double value>\n"
			<< "let <identifier>=<identifier>\n"
			<< "fn <identifier>=<identifier>\n"
			<< "fn <identifier>=<identifier><operation sign><identifier>\n"
			<< "print <identifier>\n"
			<< "printvars\n"
			<< "printfns\n";
	}
	else if (std::cin.eof())
	{
		output << "Goodbye\n";
	}
	else
	{
		output << "Unknown command\n"
			<< "Enter \"help\" for assistance\n";
	}
	output << "\n";
}

void CConsoleMenu::CommandPrintvars(std::ostream & output)
{
	if (calc.GetVariables().size() == 0)
	{
		output << "No variables\n";
	}
	else
	{
		calc.PrintVars(output);
	}
}

void CConsoleMenu::CommandPrintfns(std::ostream & output)
{
	if (calc.GetFunctions().size() == 0)
	{
		output << "No functions\n";
	}
	else
	{
		calc.PrintFns(output);
	}
}

void CConsoleMenu::CommandPrint(std::istream & stream, std::ostream & output)
{
	std::string name;
	if (!(stream >> name))
	{
		output << "Invalid argument\n"
			<< "Use command: print <identifier>\n";
		return;
	}
	if (calc.isValidName(name))
	{
		calc.Print(output, name);
		output << "\n";
	}
	else
	{
		output << "Invalid name\n"
			<< "Usage rules:\n"
			<< "1) First symbol is letter\n"
			<< "2) In name you can use: Letters, digits, and underscore\n";
	}
}

void CConsoleMenu::CommandVar(std::istream & stream, std::ostream & output)
{
	std::string name;
	if (!(stream >> name))
	{
		output << "Invalid argument\n"
			<< "Use command: var <identifier>\n";
		return;
	}
	if (calc.isValidName(name))
	{
		try
		{
			calc.Var(name);
			output << "Creating variable " << name << " successfully\n";
		}
		catch (std::invalid_argument & err)
		{
			output << err.what() << "\n";
		}
	}
	else
	{
		output << "Invalid name\n"
			<< "Usage rules:\n"
			<< "1) First symbol is letter\n"
			<< "2) In name you can use: Letters, digits, and underscore\n";
	}
}

void CConsoleMenu::CommandLet(std::istream & stream, std::ostream & output)
{
	std::string expression;
	if (!getline(stream, expression))
	{
		output << "Invalid argument\n"
			<< "Use command: let <identifier>=<identifer>\n"
			<< "let <identifier>=<double value>\n";
		return;
	}
	if (!std::regex_match(expression, std::regex(LET_PATTERN)))
	{
		output << "Invalid expression or identifier\n"
			<< "Correct expression: <identifier> = <identifier>\n"
			<< "<identifier> = <number>\n" 
			<< "\n"
			<< "Usage rules for identifier's name:\n"
			<< "1) First symbol is letter\n"
			<< "2) In name you can use: Letters, digits, and underscore\n";
		return;
	}
	auto positionEqual = expression.find("=");
	std::stringstream buffer;
	buffer << expression.substr(0, positionEqual) << " ";
	buffer << expression.substr(positionEqual + 1);
	std::string name;
	buffer >> name;
	std::string identifer;
	buffer >> identifer;
	try
	{
		if (std::regex_match(identifer, std::regex(DOUBLE_NUMBER_PATERN)))
		{
			calc.Let(name, std::stod(identifer));
			output << "Variable " << name << " has value equal " << identifer << "\n";
		}
		else
		{
			calc.Let(name, identifer);
			output << "Variable " << name << " has value equal " << calc.GetIndex(identifer)->GetResult() << "\n";
		}
	}
	catch (std::invalid_argument & err)
	{
		output << err.what() << "\n";
	}
}

void CConsoleMenu::CommandFn(std::istream & stream, std::ostream & output)
{
	std::string expression;
	if (!getline(stream, expression))
	{
		output << "Invalid argument\n"
			<< "Use command: fn <identifier>=<identifer>\n"
			<< "fn <identifier>=<identifer><operation sign><identifier>\n";
		return;
	}
	if (!std::regex_match(expression, std::regex(FN_PATTERN)))
	{
		output << "Invalid expression or identifier\n"
			<< "Correct expression: <identifier>=<identifier>\n"
			<< "<identifier>=<identifer><operation sign><identifier>\n"
			<< "\n"
			<< "Usage rules for identifier's name:\n"
			<< "1) First symbol is letter\n"
			<< "2) In name you can use: Letters, digits, and underscore\n";
		return;
	}
	auto positionEqual = expression.find("=");
	std::stringstream buffer;
	buffer << expression.substr(0, positionEqual);
	std::string name;
	buffer >> name;
	std::string firstIndex = expression.substr(positionEqual + 1);
	try
	{
		if (firstIndex.find("+") != std::string::npos)
		{
			buffer << firstIndex.substr(0, firstIndex.find("+")) + " ";
			buffer << firstIndex.substr(firstIndex.find("+") + 1);
			std::string secondIndex;
			Sign sign = Sign::plus;
			buffer >> firstIndex;
			buffer >> secondIndex;
			calc.Fn(name, firstIndex, sign, secondIndex);
			output << "Creating function " << name << " successfully\n";
		}
		else if (firstIndex.find("-") != std::string::npos)
		{
			buffer << firstIndex.substr(0, firstIndex.find("-")) + " ";
			buffer << firstIndex.substr(firstIndex.find("-") + 1);
			std::string secondIndex;
			Sign sign = Sign::minus;
			buffer >> firstIndex;
			buffer >> secondIndex;
			calc.Fn(name, firstIndex, sign, secondIndex);
			output << "Creating function " << name << " successfully\n";
		}
		else if (firstIndex.find("*") != std::string::npos)
		{
			buffer << firstIndex.substr(0, firstIndex.find("*")) + " ";
			buffer << firstIndex.substr(firstIndex.find("*") + 1);
			std::string secondIndex;
			Sign sign = Sign::factor;
			buffer >> firstIndex;
			buffer >> secondIndex;
			calc.Fn(name, firstIndex, sign, secondIndex);
			output << "Creating function " << name << " successfully\n";
		}
		else if (firstIndex.find("/") != std::string::npos)
		{
			buffer << firstIndex.substr(0, firstIndex.find("/")) + " ";
			buffer << firstIndex.substr(firstIndex.find("/") + 1);
			std::string secondIndex;
			Sign sign = Sign::minus;
			buffer >> firstIndex;
			buffer >> secondIndex;
			calc.Fn(name, firstIndex, sign, secondIndex);
			output << "Creating function " << name << " successfully\n";
		}
		else
		{
			buffer << firstIndex;
			buffer >> firstIndex;
			calc.Fn(name, firstIndex);
			output << "Creating function " << name << " successfully\n";
		}
	}
	catch (std::invalid_argument & err)
	{
		output << err.what() << "\n";
	}
}

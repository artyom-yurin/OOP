#include "stdafx.h"
#include "ConsoleMenu.h"
#include "ShapesFunctions.h"

void CConsoleMenu::RunCommand(std::istream & stream)
{
	std::string command;
	stream >> command;
	if (command == "rectangle")
	{
		RectangleCommand(stream, m_shapes);
	}
	else if (command == "triangle")
	{
		TriangleCommand(stream, m_shapes);
	}
	else if (command == "circle")
	{
		CircleCommand(stream, m_shapes);
	}
	else if (command == "line")
	{
		LineCommand(stream, m_shapes);
	}
	else if (command == "help")
	{
		std::cout << "Using:\n"
			<< "rectangle <x value> <y value> <width> <height> <outline color> <fill color>\n"
			<< "triangle <x1 value> <y1 value>  <x2 value> <y2 value> <x3 value> <y3 value> <outline color> <fill color>\n"
			<< "circle <center x value> <center y value>  <radius> <outline color> <fill color>\n"
			<< "line <start x value> <start y value> <end x value> <end y value> <outline color>\n";
	}
	else if (std::cin.eof())
	{
		if (!m_shapes.empty())
		{
			std::cout << "Shape with large area: " << ToString(GetLargeAreaShape(m_shapes)) << "\n"
				<< "\n"
				<< "Shape with small perimetr: " << ToString(GetSmallPerimeterShape(m_shapes)) << "\n";
		}
		else
		{
			std::cout << "No shapes\n";
		}
	}
	else
	{
		std::cout << "Unknown command\n"
			<< "Enter \"help\" for assistance\n";
	}
	std::cout << "\n";
}

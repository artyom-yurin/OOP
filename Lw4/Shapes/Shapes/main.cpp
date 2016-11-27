#include "stdafx.h"
#include "Circle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "ShapesFunctions.h"

int main()
{
	std::vector<std::shared_ptr<IShape>> shapes;
	while (!std::cin.eof())
	{
		std::stringstream buffer;
		std::string command;
		std::cout << "Enter command: ";
		getline(std::cin, command);
		buffer << command;
		buffer >> command;
		std::cout << "\n";
		if (command == "rectangle")
		{
			RectangleCommand(buffer, shapes);
		}
		else if (command == "triangle")
		{
			TriangleCommand(buffer, shapes);
		}
		else if (command == "circle")
		{
			CircleCommand(buffer, shapes);
		}
		else if (command == "line")
		{
			LineCommand(buffer, shapes);
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
			if (!shapes.empty())
			{
				std::cout << "Shape with large area: " << ToString(GetLargeAreaShape(shapes)) << "\n"
					<< "\n"
					<< "Shape with small perimetr: " << ToString(GetSmallPerimeterShape(shapes)) << "\n";
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
    return 0;
}

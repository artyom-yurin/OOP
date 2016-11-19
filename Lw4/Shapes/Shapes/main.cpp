#include "stdafx.h"
#include "Shapes.h"
#include "ShapesFunctions.h"

int main()
{
	std::vector<std::shared_ptr<IShape>> shapes;
	while (!std::cin.eof())
	{
		std::stringstream buffer;
		std::string command;
		std::cin >> command;
		buffer << command;
		buffer >> command;
		if (command == "rectangle")
		{

		}
		else if (command == "triangle")
		{

		}
		else if (command == "circle")
		{

		}
		else if (command == "line")
		{

		}
		else if (command == "help")
		{
			std::cout << "	Using:\n"
				<< "	rectangle <x value> <y value> <width> <height> <outline color> <fill color>\n"
				<< "	triangle <x1 value> <y1 value>  <x2 value> <y2 value> <x3 value> <y3 value> <outline color> <fill color>\n"
				<< "	circle <center x value> <center y value>  <radius> <outline color> <fill color>\n"
				<< "	line <start x value> <start y value> <end x value> <end y value> <outline color>\n";
		}
		else if (std::cin.eof())
		{
			std::cout << "Shape with large area: " << GetLargeAreaShape(shapes)->ToString() << "\n"
				<< "Shape with small perimetr: " << GetSmallPerimetrShape(shapes)->ToString() << "\n";
		}
		else
		{
			std::cout << "	Unknown command\n"
				<< "	Enter \"help\" for assistance\n";
		}
	}
    return 0;
}


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
		std::cout << "Enter command: ";
		getline(std::cin, command);
		buffer << command;
		buffer >> command;
		if (command == "rectangle")
		{
			SPoint vertex;
			double width;
			double height;
			std::string outlineColor;
			std::string fillColor;
			if ((buffer >> vertex.x) && (buffer >> vertex.y))
			{
				if ((buffer >> width) && (buffer >> height))
				{
					if ((buffer >> outlineColor) && (buffer >> fillColor))
					{
						if (CorrectColor(outlineColor) && CorrectColor(fillColor))
						{
							shapes.push_back(std::make_shared<CRectangle>(vertex, width, height, outlineColor, fillColor));
							std::cout << "Rectangle was created\n";
						}
						else
						{
							std::cout << "Invalid color\n"
								<< "Use 16 hexadecimal code\n";
						}
					}
					else
					{
						std::cout << "Error color value\n";
					}
				}
				else
				{
					std::cout << "Error size value\n";
				}

			}
			else
			{
				std::cout << "Error vertex value\n";
			}
			
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
				std::cout << "Shape with large area: " << GetLargeAreaShape(shapes)->ToString() << "\n"
					<< "\n"
					<< "Shape with small perimetr: " << GetSmallPerimetrShape(shapes)->ToString() << "\n";
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
	}
    return 0;
}


#include "stdafx.h"
#include "Triangle.h"
#include "Circle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "ShapesFunctions.h"

std::string ToString(std::shared_ptr<IShape> const & shape)
{
	std::stringstream buffer;

	buffer << std::fixed << std::setprecision(2);

	buffer << shape->GetName() << " "
		<< shape->GetSpecialInfo() << " "
		<< "Area = " 
		<< shape->GetArea() << " "
		<< "Perimeter = "
		<< shape->GetPerimeter() << " "
		<< "Outline color = #"
		<< shape->GetOutlineColor();

	return buffer.str();
}

std::shared_ptr<IShape> GetLargeAreaShape(std::vector<std::shared_ptr<IShape>> const & shapes)
{
	if (shapes.empty())
	{
		throw std::invalid_argument("vector shapes can not be empty");
	}
	auto maxArea = std::max_element(shapes.cbegin(), shapes.cend(), [](const auto & arg1, const auto & arg2) {
		return arg1->GetArea() < arg2->GetArea();
	});
	return *maxArea;
}

std::shared_ptr<IShape> GetSmallPerimeterShape(std::vector<std::shared_ptr<IShape>> const & shapes)
{
	if (shapes.empty())
	{
		throw std::invalid_argument("vector shapes can not be empty");
	}
	auto minPerimeter = std::min_element(shapes.cbegin(), shapes.cend(), [](const auto & arg1, const auto & arg2) {
		return arg1->GetPerimeter() < arg2->GetPerimeter();
	});
	return *minPerimeter;
}

bool IsColorCorrect(std::string const & color)
{
	if (color.length() != 6)
	{
		return false;
	}

	for (char symbol : color)
	{
		if (!((symbol <= 'F' && symbol >= 'A') || (symbol <= 'f' && symbol >= 'a') || (symbol <= '9' && symbol >= '0')))
		{
			return false;
		}
	}

	return true;
}

void RectangleCommand(std::istream & stream, std::vector<std::shared_ptr<IShape>> & shapes)
{
	SPoint vertex;
	double width;
	double height;
	std::string outlineColor;
	std::string fillColor;
	if ((stream >> vertex.x) && (stream >> vertex.y))
	{
		std::cout << "Error vertex value\n";
		return;
	}
	if ((stream >> width) && (stream >> height))
	{
		std::cout << "Error size value\n";
		return;
	}
	if ((stream >> outlineColor) && (stream >> fillColor))
	{
		std::cout << "Error color value\n";
		return;
	}
	if (IsColorCorrect(outlineColor) && IsColorCorrect(fillColor))
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

void TriangleCommand(std::istream & stream, std::vector<std::shared_ptr<IShape>>& shapes)
{
	SPoint vertex1;
	SPoint vertex2;
	SPoint vertex3;
	std::string outlineColor;
	std::string fillColor;
	if ((stream >> vertex1.x) && (stream >> vertex1.y))
	{
		std::cout << "Error vertex 1 value\n";
		return;
	}
	if ((stream >> vertex2.x) && (stream >> vertex2.y))
	{
		std::cout << "Error vertex 2 value\n";
		return;
	}
	if ((stream >> vertex3.x) && (stream >> vertex3.y))
	{
		std::cout << "Error vertex 3 value\n";
		return;
	}
	if ((stream >> outlineColor) && (stream >> fillColor))
	{
		std::cout << "Error color value\n";
		return;
	}
	if (IsColorCorrect(outlineColor) && IsColorCorrect(fillColor))
	{
		shapes.push_back(std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor));
		std::cout << "Triangle was created\n";
	}
	else
	{
		std::cout << "Invalid color\n"
			<< "Use 16 hexadecimal code\n";
	}
}

void CircleCommand(std::istream & stream, std::vector<std::shared_ptr<IShape>>& shapes)
{
	SPoint center;
	double radius;
	std::string outlineColor;
	std::string fillColor;
	if ((stream >> center.x) && (stream >> center.y))
	{
		std::cout << "Error center value\n";
		return;
	}
	if (stream >> radius)
	{
		std::cout << "Error radius value\n";
		return;
	}
	if ((stream >> outlineColor) && (stream >> fillColor))
	{
		std::cout << "Error color value\n";
		return;
	}
	if (IsColorCorrect(outlineColor) && IsColorCorrect(fillColor))
	{
		shapes.push_back(std::make_shared<CCircle>(center, radius, outlineColor, fillColor));
		std::cout << "Circle was created\n";
	}
	else
	{
		std::cout << "Invalid color\n"
			<< "Use 16 hexadecimal code\n";
	}
}

void LineCommand(std::istream & stream, std::vector<std::shared_ptr<IShape>>& shapes)
{
	SPoint startPoint;
	SPoint endPoint;
	std::string outlineColor;
	if ((stream >> startPoint.x) && (stream >> startPoint.y))
	{
		std::cout << "Error start point value\n";
		return;
	}
	if ((stream >> endPoint.x) && (stream >> endPoint.y))
	{
		std::cout << "Error end point value\n";
		return;
	}
	if ((stream >> outlineColor))
	{
		std::cout << "Error color value\n";
		return;
	}
	if (IsColorCorrect(outlineColor))
	{
		shapes.push_back(std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor));
		std::cout << "Line was created\n";
	}
	else
	{
		std::cout << "Invalid color\n"
			<< "Use 16 hexadecimal code\n";
	}
}

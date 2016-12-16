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
	return std::all_of(color.cbegin(), color.cend(), [](char symbol) {
		return (symbol >= 'A' && symbol <= 'F') ||
			(symbol >= 'a' && symbol <= 'f') || 
			(symbol >= '0' && symbol <= '9');
	});
}

void RectangleCommand(std::istream & stream, std::ostream & output, std::vector<std::shared_ptr<IShape>> & shapes)
{
	SPoint vertex;
	double width;
	double height;
	std::string outlineColor;
	std::string fillColor;
	if (!((stream >> vertex.x) && (stream >> vertex.y)))
	{
		output << "Error vertex value\n";
		return;
	}
	if (!((stream >> width) && (stream >> height)))
	{
		output << "Error size value\n";
		return;
	}
	if (!((stream >> outlineColor) && (stream >> fillColor)))
	{
		output << "Error color value\n";
		return;
	}
	if (IsColorCorrect(outlineColor) && IsColorCorrect(fillColor))
	{
		shapes.push_back(std::make_shared<CRectangle>(vertex, width, height, outlineColor, fillColor));
		output << "Rectangle was created\n";
	}
	else
	{
		output << "Invalid color\n"
			<< "Use 16 hexadecimal code\n";
	}
}

void TriangleCommand(std::istream & stream, std::ostream & output, std::vector<std::shared_ptr<IShape>>& shapes)
{
	SPoint vertex1;
	SPoint vertex2;
	SPoint vertex3;
	std::string outlineColor;
	std::string fillColor;
	if (!((stream >> vertex1.x) && (stream >> vertex1.y)))
	{
		output << "Error vertex 1 value\n";
		return;
	}
	if (!((stream >> vertex2.x) && (stream >> vertex2.y)))
	{
		output << "Error vertex 2 value\n";
		return;
	}
	if (!((stream >> vertex3.x) && (stream >> vertex3.y)))
	{
		output << "Error vertex 3 value\n";
		return;
	}
	if (!((stream >> outlineColor) && (stream >> fillColor)))
	{
		output << "Error color value\n";
		return;
	}
	if (IsColorCorrect(outlineColor) && IsColorCorrect(fillColor))
	{
		shapes.push_back(std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor));
		output << "Triangle was created\n";
	}
	else
	{
		output << "Invalid color\n"
			<< "Use 16 hexadecimal code\n";
	}
}

void CircleCommand(std::istream & stream, std::ostream & output, std::vector<std::shared_ptr<IShape>>& shapes)
{
	SPoint center;
	double radius;
	std::string outlineColor;
	std::string fillColor;
	if (!((stream >> center.x) && (stream >> center.y)))
	{
		output << "Error center value\n";
		return;
	}
	if (!(stream >> radius))
	{
		output << "Error radius value\n";
		return;
	}
	if (!((stream >> outlineColor) && (stream >> fillColor)))
	{
		output << "Error color value\n";
		return;
	}
	if (IsColorCorrect(outlineColor) && IsColorCorrect(fillColor))
	{
		shapes.push_back(std::make_shared<CCircle>(center, radius, outlineColor, fillColor));
		output << "Circle was created\n";
	}
	else
	{
		output << "Invalid color\n"
			<< "Use 16 hexadecimal code\n";
	}
}

void LineCommand(std::istream & stream, std::ostream & output, std::vector<std::shared_ptr<IShape>>& shapes)
{
	SPoint startPoint;
	SPoint endPoint;
	std::string outlineColor;
	if (!((stream >> startPoint.x) && (stream >> startPoint.y)))
	{
		output << "Error start point value\n";
		return;
	}
	if (!((stream >> endPoint.x) && (stream >> endPoint.y)))
	{
		output << "Error end point value\n";
		return;
	}
	if (!((stream >> outlineColor)))
	{
		output << "Error color value\n";
		return;
	}
	if (IsColorCorrect(outlineColor))
	{
		shapes.push_back(std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor));
		output << "Line was created\n";
	}
	else
	{
		output << "Invalid color\n"
			<< "Use 16 hexadecimal code\n";
	}
}

#include "stdafx.h"
#include "Shapes.h"
#include "ShapesFunctions.h"

std::shared_ptr<IShape> GetLargeAreaShape(std::vector<std::shared_ptr<IShape>> const & shapes)
{
	std::shared_ptr<IShape> result = nullptr;

	for (std::shared_ptr<IShape> shape : shapes)
	{
		if ((result == nullptr) || (shape->GetArea() > result->GetArea()))
		{
			result = shape;
		}
	}

	return result;
}

std::shared_ptr<IShape> GetSmallPerimetrShape(std::vector<std::shared_ptr<IShape>> const & shapes)
{
	std::shared_ptr<IShape> result = nullptr;

	for (std::shared_ptr<IShape> shape : shapes)
	{
		if ((result == nullptr) || (shape->GetPerimeter() < result->GetPerimeter()))
		{
			result = shape;
		}
	}

	return result;
}

bool CorrectColor(std::string const & color)
{
	if (color.length() != 6)
	{
		return false;
	}

	for (char symbol : color)
	{
		if (symbol != 'F' &&
			symbol != 'E' &&
			symbol != 'D' &&
			symbol != 'C' &&
			symbol != 'B' &&
			symbol != 'A' &&
			symbol != '9' &&
			symbol != '8' &&
			symbol != '7' &&
			symbol != '6' &&
			symbol != '5' &&
			symbol != '4' &&
			symbol != '3' &&
			symbol != '2' &&
			symbol != '1' &&
			symbol != '0')
		{
			return false;
		}
	}

	return true;
}

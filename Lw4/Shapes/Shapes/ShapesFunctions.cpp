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
		if (!((symbol <= 'F' && symbol >= 'A') || (symbol <= 'f' && symbol >= 'a') || (symbol <= '9' && symbol >= '0')))
		{
			return false;
		}
	}

	return true;
}

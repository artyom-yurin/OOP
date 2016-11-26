#include "stdafx.h"
#include "Shapes.h"
#include "ShapesFunctions.h"

std::shared_ptr<IShape> GetLargeAreaShape(std::vector<std::shared_ptr<IShape>> const & shapes)
{
	auto maxArea = std::max_element(shapes.cbegin(), shapes.cend(), [](const auto & arg1, const auto & arg2) {
		return arg1->GetArea() < arg2->GetArea();
	});
	return *maxArea;
}

std::shared_ptr<IShape> GetSmallPerimeterShape(std::vector<std::shared_ptr<IShape>> const & shapes)
{
	auto minPerimeter = std::min_element(shapes.cbegin(), shapes.cend(), [](const auto & arg1, const auto & arg2) {
		return arg1->GetPerimeter() < arg2->GetPerimeter();
	});
	return *minPerimeter;
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

#include "stdafx.h"

#include "../Shapes/Triangle.h"
#include "../Shapes/Circle.h"
#include "../Shapes/Rectangle.h"
#include "../Shapes/LineSegment.h"
#include "../Shapes/ShapesFunctions.h"

#define _VARIADIC_MAX

struct VectorShapeFixture
{
	std::vector<std::shared_ptr<IShape>> shapes;
	SPoint center = { 0 ,0 };
	SPoint vertex1 = { -1, 1 };
	SPoint vertex2 = { -1, -1 };
	double width = 10;
	double height = 20;
	VectorShapeFixture()
	{
		shapes.push_back(std::make_shared<CCircle>(center, 10, "FFFFFF", "000000"));
		shapes.push_back(std::make_shared<CCircle>(center, 30, "FFFFFF", "000000"));
		shapes.push_back(std::make_shared<CTriangle>(center, vertex1, vertex2, "FFFFFF", "000000"));
		shapes.push_back(std::make_shared<CRectangle>(center, width, height, "FFFFFF", "000000"));
	}
};


BOOST_FIXTURE_TEST_SUITE(VectorFunction, VectorShapeFixture)

	BOOST_AUTO_TEST_CASE(get_shape_with_max_area_value)
	{
		std::shared_ptr<IShape> shape = GetLargeAreaShape(shapes);
		BOOST_CHECK_EQUAL(ToString(shape), "circle Center (0.00, 0.00) Radius = 30.00 Fill color = #000000 Area = 2827.43 Perimeter = 188.50 Outline color = #FFFFFF");
	}

	BOOST_AUTO_TEST_CASE(get_shape_with_min_perimetr_value)
	{
		std::shared_ptr<IShape> shape = GetSmallPerimeterShape(shapes);
		BOOST_CHECK_EQUAL(ToString(shape), "triangle Vertex 1 (0.00, 0.00) Vertex 2 (-1.00, 1.00) Vertex 3 (-1.00, -1.00) Fill color = #000000 Area = 1.00 Perimeter = 4.83 Outline color = #FFFFFF");
	}

BOOST_AUTO_TEST_SUITE_END()
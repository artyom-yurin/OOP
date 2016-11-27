#include "stdafx.h"

#include "../Shapes/Triangle.h"
#include "../Shapes/Circle.h"
#include "../Shapes/Rectangle.h"
#include "../Shapes/LineSegment.h"

void CheckCoordinates(SPoint const & currentCoordinates, SPoint const & correctCoordinates)
{
	BOOST_CHECK_EQUAL(currentCoordinates.x, correctCoordinates.x);
	BOOST_CHECK_EQUAL(currentCoordinates.y, correctCoordinates.y);
}

struct TriangleFixture
{
	const SPoint vertex1 = { 1, 1 };
	const SPoint vertex2 = { 1, 4 };
	const SPoint vertex3 = { 5, 1 };
	const std::string outlineColor = "000000";
	const std::string fillColor = "FFFFFF";
	const CTriangle triangle;
	TriangleFixture()
		: triangle(vertex1, vertex2, vertex3, outlineColor, fillColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Triangle, TriangleFixture)

	BOOST_AUTO_TEST_CASE(has_first_vertex)
	{
		CheckCoordinates(triangle.GetVertex1(), vertex1);
	}

	BOOST_AUTO_TEST_CASE(has_second_vertex)
	{
		CheckCoordinates(triangle.GetVertex2(), vertex2);
	}

	BOOST_AUTO_TEST_CASE(has_third_vertex)
	{
		CheckCoordinates(triangle.GetVertex3(), vertex3);
	}

	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK_EQUAL(triangle.GetOutlineColor(), outlineColor);
	}

	BOOST_AUTO_TEST_CASE(has_fill_color)
	{
		BOOST_CHECK_EQUAL(triangle.GetFillColor(), fillColor);
	}

	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		BOOST_CHECK_EQUAL(triangle.GetPerimeter(), 12);
	}

	BOOST_AUTO_TEST_CASE(can_find_area)
	{
		BOOST_CHECK_EQUAL(triangle.GetArea(), 6);
	}

	BOOST_AUTO_TEST_CASE(can_get_name)
	{
		BOOST_CHECK_EQUAL(triangle.GetName(), "triangle");
	}

	BOOST_AUTO_TEST_CASE(can_get_special_info)
	{
		BOOST_CHECK_EQUAL(triangle.GetSpecialInfo(), "Vertex 1 (1.00, 1.00) Vertex 2 (1.00, 4.00) Vertex 3 (5.00, 1.00) Fill color = #FFFFFF");
	}
BOOST_AUTO_TEST_SUITE_END()

struct RectangleFixture
{
	const SPoint leftTopVertex = { 0, 0 };
	const double width = 10;
	const double height = 20;
	const std::string outlineColor = "000000";
	const std::string fillColor = "FFFFFF";
	CRectangle rectangle;
	RectangleFixture()
		: rectangle(leftTopVertex, width, height, outlineColor, fillColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Rectangle, RectangleFixture)

	BOOST_AUTO_TEST_CASE(has_left_top_vertex)
	{
		CheckCoordinates(rectangle.GetLeftTop(), leftTopVertex);
	}

	BOOST_AUTO_TEST_CASE(has_right_bottom_vertex)
	{
		CheckCoordinates(rectangle.GetRightBottom(), {leftTopVertex.x + width, leftTopVertex.y + height});
	}

	BOOST_AUTO_TEST_CASE(has_width)
	{
		BOOST_CHECK_EQUAL(rectangle.GetWidth(), width);
	}

	BOOST_AUTO_TEST_CASE(has_height)
	{
		BOOST_CHECK_EQUAL(rectangle.GetHeight(), height);
	}

	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK_EQUAL(rectangle.GetOutlineColor(), outlineColor);
	}

	BOOST_AUTO_TEST_CASE(has_fill_color)
	{
		BOOST_CHECK_EQUAL(rectangle.GetFillColor(), fillColor);
	}

	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		BOOST_CHECK_EQUAL(rectangle.GetPerimeter(), 60);
	}

	BOOST_AUTO_TEST_CASE(can_find_area)
	{
		BOOST_CHECK_EQUAL(rectangle.GetArea(), 200);
	}

	BOOST_AUTO_TEST_CASE(can_get_name)
	{
		BOOST_CHECK_EQUAL(rectangle.GetName(), "rectangle");
	}

	BOOST_AUTO_TEST_CASE(can_get_special_info)
	{
		BOOST_CHECK_EQUAL(rectangle.GetSpecialInfo(), "Left top point (0.00, 0.00) Right bottom point(10.00, 20.00) Width = 10.00 Height = 20.00 Fill color = #FFFFFF");
	}

BOOST_AUTO_TEST_SUITE_END()

struct CircleFixture
{
	const SPoint center = { 0, 0 };
	const double radius = 10;
	const std::string outlineColor = "000000";
	const std::string fillColor = "FFFFFF";
	CCircle circle;
	CircleFixture()
		: circle(center, radius, outlineColor, fillColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Circle, CircleFixture)

	BOOST_AUTO_TEST_CASE(has_center)
	{
		CheckCoordinates(circle.GetCenter(), center);
	}

	BOOST_AUTO_TEST_CASE(has_radius)
	{
		BOOST_CHECK_EQUAL(circle.GetRadius(), radius);
	}

	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK_EQUAL(circle.GetOutlineColor(), outlineColor);
	}

	BOOST_AUTO_TEST_CASE(has_fill_color)
	{
		BOOST_CHECK_EQUAL(circle.GetFillColor(), fillColor);
	}

	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(circle.GetPerimeter()), 62);
	}

	BOOST_AUTO_TEST_CASE(can_find_area)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(circle.GetArea()), 314);
	}

	BOOST_AUTO_TEST_CASE(can_get_name)
	{
		BOOST_CHECK_EQUAL(circle.GetName(), "circle");
	}

	BOOST_AUTO_TEST_CASE(can_get_special_info)
	{
		BOOST_CHECK_EQUAL(circle.GetSpecialInfo(), "Center (0.00, 0.00) Radius = 10.00 Fill color = #FFFFFF");
	}

BOOST_AUTO_TEST_SUITE_END()

struct LineSegmentFixture
{
	const SPoint startPoint = { 0, 0 };
	const SPoint endPoint = { 1, 1 };
	const std::string outlineColor = "000000";
	CLineSegment line;
	LineSegmentFixture()
		: line(startPoint, endPoint, outlineColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(LineSegment, LineSegmentFixture)

	BOOST_AUTO_TEST_CASE(has_start_point)
	{
		CheckCoordinates(line.GetStartPoint(), startPoint);
	}

	BOOST_AUTO_TEST_CASE(has_end_point)
	{
		CheckCoordinates(line.GetEndPoint(), endPoint);
	}

	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK_EQUAL(line.GetOutlineColor(), outlineColor);
	}

	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(line.GetPerimeter()), 1);
	}

	BOOST_AUTO_TEST_CASE(can_find_area)
	{
		BOOST_CHECK_EQUAL(line.GetArea(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_get_name)
	{
		BOOST_CHECK_EQUAL(line.GetName(), "line");
	}

	BOOST_AUTO_TEST_CASE(can_get_special_info)
	{
		BOOST_CHECK_EQUAL(line.GetSpecialInfo(), "Start point (0.00, 0.00) End point (1.00, 1.00)");
	}

BOOST_AUTO_TEST_SUITE_END()

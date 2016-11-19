#include "stdafx.h"

#include "..\Shapes\Shapes.h"

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

	BOOST_AUTO_TEST_CASE(can_convert_to_string)
	{
		BOOST_CHECK_EQUAL(triangle.ToString(), "triangle Vertex 1 (1.00, 1.00) Vertex 2 (1.00, 4.00) Vertex 3 (5.00, 1.00) Perimetr = 12.00 Area = 6.00 Outline color = #000000 Fill color = #FFFFFF");
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

	BOOST_AUTO_TEST_CASE(can_convert_to_string)
	{
		BOOST_CHECK_EQUAL(rectangle.ToString(), "rectangle Left top vertex (0.00, 0.00) Right bottom vertex (10.00, 20.00) Width = 10.00 Height = 20.00 Perimetr = 60.00 Area = 200.00 Outline color = #000000 Fill color = #FFFFFF");
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

	BOOST_AUTO_TEST_CASE(can_convert_to_string)
	{
		BOOST_CHECK_EQUAL(circle.ToString(), "circle Center (0.00, 0.00) Radius = 10.00 Perimetr = 62.83 Area = 314.16 Outline color = #000000 Fill color = #FFFFFF");
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

	BOOST_AUTO_TEST_CASE(can_convert_to_string)
	{
		BOOST_CHECK_EQUAL(line.ToString(), "line Start point (0.00, 0.00) End point (1.00, 1.00) Perimetr = 1.41 Area = 0.00 Outline color = #000000");
	}

BOOST_AUTO_TEST_SUITE_END()

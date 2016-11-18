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
	const SPoint vertex2 = { -2, 4 };
	const SPoint vertex3 = { -2, -2 };
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

BOOST_AUTO_TEST_SUITE_END()
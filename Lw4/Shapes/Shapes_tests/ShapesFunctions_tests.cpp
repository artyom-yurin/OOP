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
	
	BOOST_AUTO_TEST_CASE(color_check)
	{	
		BOOST_CHECK(IsColorCorrect("FF00ff"));
		BOOST_CHECK(!IsColorCorrect("FF00fG"));
	}

	BOOST_AUTO_TEST_CASE(not_process_empty_vector)
	{
		std::vector<std::shared_ptr<IShape>> emptyVector;
		try
		{
			GetLargeAreaShape(emptyVector);
		}
		catch(std::invalid_argument const & e)
		{
			BOOST_CHECK_EQUAL(e.what(), "vector shapes can not be empty");
		}
		try
		{
			GetSmallPerimeterShape(emptyVector);
		}
		catch (std::invalid_argument const & e)
		{
			BOOST_CHECK_EQUAL(e.what(), "vector shapes can not be empty");
		}
	}
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

BOOST_AUTO_TEST_SUITE(ShapesFunctions)
	
	BOOST_AUTO_TEST_SUITE(RectangleCommand_function)

		BOOST_AUTO_TEST_CASE(error_vertex_value)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			RectangleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Error vertex value\n");
		}
		
		BOOST_AUTO_TEST_CASE(error_size_value)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0";
			RectangleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Error size value\n");
		}

		BOOST_AUTO_TEST_CASE(error_color_value)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0 0 0";
			RectangleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Error color value\n");
		}

		BOOST_AUTO_TEST_CASE(invalid_color)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0 0 0 ffggff ffffff";
			RectangleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Invalid color\nUse 16 hexadecimal code\n");
		}

		BOOST_AUTO_TEST_CASE(correct_data)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0 0 0 ffFFff ffffff";
			RectangleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Rectangle was created\n");
			BOOST_CHECK(!shapes.empty());
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(TriangleCommand_function)

		BOOST_AUTO_TEST_CASE(error_vertex_1_value)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			TriangleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Error vertex 1 value\n");
		}

		BOOST_AUTO_TEST_CASE(error_vertex_2_value)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0";
			TriangleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Error vertex 2 value\n");
		}

		BOOST_AUTO_TEST_CASE(error_vertex_3_value)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0 0 0";
			TriangleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Error vertex 3 value\n");
		}

		BOOST_AUTO_TEST_CASE(error_color_value)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0 0 0 0 0";
			TriangleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Error color value\n");
		}

		BOOST_AUTO_TEST_CASE(invalid_color)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0 0 0 0 0 ffggff ffffff";
			TriangleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Invalid color\nUse 16 hexadecimal code\n");
		}

		BOOST_AUTO_TEST_CASE(correct_data)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0 0 0 0 0 ffFFff ffffff";
			TriangleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Triangle was created\n");
			BOOST_CHECK(!shapes.empty());
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(CircleCommand_function)

		BOOST_AUTO_TEST_CASE(error_center_value)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			CircleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Error center value\n");
		}

		BOOST_AUTO_TEST_CASE(error_radius_value)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0";
			CircleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Error radius value\n");
		}

		BOOST_AUTO_TEST_CASE(error_color_value)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0 10";
			CircleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Error color value\n");
		}

		BOOST_AUTO_TEST_CASE(invalid_color)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0 10 ffggff ffffff";
			CircleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Invalid color\nUse 16 hexadecimal code\n");
		}

		BOOST_AUTO_TEST_CASE(correct_data)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0 10 ffFFff ffffff";
			CircleCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Circle was created\n");
			BOOST_CHECK(!shapes.empty());
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(LineCommand_function)

		BOOST_AUTO_TEST_CASE(error_vertex_1_value)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			LineCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Error start point value\n");
		}

		BOOST_AUTO_TEST_CASE(error_vertex_2_value)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0";
			LineCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Error end point value\n");
		}

		BOOST_AUTO_TEST_CASE(error_color_value)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0 0 0";
			LineCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Error color value\n");
		}

		BOOST_AUTO_TEST_CASE(invalid_color)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0 0 0 ffggff ffffff";
			LineCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Invalid color\nUse 16 hexadecimal code\n");
		}

		BOOST_AUTO_TEST_CASE(correct_data)
		{
			std::stringstream input;
			std::stringstream output;
			std::vector<std::shared_ptr<IShape>> shapes;
			input << "0 0 0 0 ffFFff ffffff";
			LineCommand(input, output, shapes);
			BOOST_CHECK_EQUAL(output.str(), "Line was created\n");
			BOOST_CHECK(!shapes.empty());
		}

	BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()

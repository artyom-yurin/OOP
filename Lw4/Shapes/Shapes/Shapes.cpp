#include "stdafx.h"
#include "Shapes.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <tuple>

CTriangle::CTriangle(SPoint const & vertex1, SPoint const & vertex2, SPoint const & vertex3, std::string const & outlineColor, std::string const & fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{}

SPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

SPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

SPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

std::string CTriangle::GetFillColor() const
{
	return m_fillColor;
}

std::string CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

double CTriangle::GetArea() const
{
	double firstSide;
	double secondSide;
	double thirdSide;
	std::tie(firstSide, secondSide, thirdSide) = GetSides();
	double perimeterHalf = CTriangle::GetPerimeter() * 0.5;
	return std::round(100 * sqrt(perimeterHalf * (perimeterHalf - firstSide) * (perimeterHalf - secondSide) * (perimeterHalf - thirdSide))) / 100;
}

double CTriangle::GetPerimeter() const
{
	double firstSide;
	double secondSide;
	double thirdSide;
	std::tie(firstSide, secondSide, thirdSide) = GetSides();
	return firstSide + secondSide + thirdSide;
}

std::string CTriangle::ToString() const
{
	std::stringstream buffer;

	buffer << std::fixed << std::setprecision(2);

	buffer << "triangle "
		<< "Vertex 1 (" << m_vertex1.x << ", " << m_vertex1.y << ") "
		<< "Vertex 2 (" << m_vertex2.x << ", " << m_vertex2.y << ") "
		<< "Vertex 3 (" << m_vertex3.x << ", " << m_vertex3.y << ") "
		<< "Perimetr = " << CTriangle::GetPerimeter() << " "
		<< "Area = " << CTriangle::GetArea() << " "
		<< "Outline color = #" << CTriangle::GetOutlineColor() << " "
		<< "Fill color = #" << CTriangle::GetFillColor();

	return buffer.str();
}

std::tuple<double, double, double> CTriangle::GetSides() const
{
	double firstSide = hypot(m_vertex1.x - m_vertex2.x, m_vertex1.y - m_vertex2.y);
	double secondSide = hypot(m_vertex1.x - m_vertex3.x, m_vertex1.y - m_vertex3.y);
	double thirdSide = hypot(m_vertex3.x - m_vertex2.x, m_vertex3.y - m_vertex2.y);
	return std::make_tuple(firstSide, secondSide, thirdSide);
}

CRectangle::CRectangle(SPoint const & leftTopVertex, double const & width, double const & height, std::string const & outlineColor, std::string const & fillColor)
	:m_leftTopVertex(leftTopVertex),
	m_width(width),
	m_height(height),
	m_outlineColor(outlineColor),
	m_fillColor(fillColor)
{}

SPoint CRectangle::GetLeftTop() const
{
	return m_leftTopVertex;
}

SPoint CRectangle::GetRightBottom() const
{
	return {m_leftTopVertex.x + m_width, m_leftTopVertex.y + m_height};
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

std::string CRectangle::GetFillColor() const
{
	return m_fillColor;
}

std::string CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

std::string CRectangle::ToString() const
{
	std::stringstream buffer;

	buffer << std::fixed << std::setprecision(2);

	buffer << "rectangle "
		<< "Left top vertex (" << m_leftTopVertex.x << ", " << m_leftTopVertex.y << ") "
		<< "Right bottom vertex (" << GetRightBottom().x << ", " << GetRightBottom().y << ") "
		<< "Width = " << m_width << " "
		<< "Height = " << m_height << " "
		<< "Perimetr = " << CRectangle::GetPerimeter() << " "
		<< "Area = " << CRectangle::GetArea() << " "
		<< "Outline color = #" << CRectangle::GetOutlineColor() << " "
		<< "Fill color = #" << CRectangle::GetFillColor();

	return buffer.str();
}

CCircle::CCircle(SPoint const & center, double const & radius, std::string const & outlineColor, std::string const & fillColor)
	: m_center(center),
	m_radius(radius),
	m_fillColor(fillColor),
	m_outlineColor(outlineColor)
{}

SPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

std::string CCircle::GetFillColor() const
{
	return m_fillColor;
}

std::string CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return M_PI * 2 * m_radius;
}

std::string CCircle::ToString() const
{
	std::stringstream buffer;

	buffer << std::fixed << std::setprecision(2);

	buffer << "circle "
		<< "Center (" << m_center.x << ", " << m_center.y << ") "
		<< "Radius = " << m_radius << " "
		<< "Perimetr = " << CCircle::GetPerimeter() << " "
		<< "Area = " << CCircle::GetArea() << " "
		<< "Outline color = #" << CCircle::GetOutlineColor() << " "
		<< "Fill color = #" << CCircle::GetFillColor();

	return buffer.str();
}

CLineSegment::CLineSegment(SPoint const & startPoint, SPoint const & endPoint, std::string const & outlineColor)
	: m_startPoint(startPoint),
	m_endPoint(endPoint),
	m_outlineColor(outlineColor)
{}

SPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

SPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

std::string CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return hypot(m_endPoint.x - m_startPoint.x, m_endPoint.y - m_startPoint.y);
}

std::string CLineSegment::ToString() const
{
	std::stringstream buffer;

	buffer << std::fixed << std::setprecision(2);

	buffer << "line "
		<< "Start point (" << m_startPoint.x << ", " << m_startPoint.y << ") "
		<< "End point (" << m_endPoint.x << ", " << m_endPoint.y << ") "
		<< "Perimetr = " << CLineSegment::GetPerimeter() << " "
		<< "Area = " << CLineSegment::GetArea() << " "
		<< "Outline color = #" << CLineSegment::GetOutlineColor();

	return buffer.str();
}

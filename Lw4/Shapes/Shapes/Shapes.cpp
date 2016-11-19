#include "stdafx.h"
#include "Shapes.h"

CTriangle::CTriangle(SPoint const & vertex1, SPoint const & vertex2, SPoint const & vertex3, std::string const & outlineColor, std::string const & fillColor)
	:m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	m_firstSide = hypot(m_vertex1.x - m_vertex2.x, m_vertex1.y - m_vertex2.y);
	m_secondSide = hypot(m_vertex1.x - m_vertex3.x, m_vertex1.y - m_vertex3.y);
	m_thirdSide = hypot(m_vertex3.x - m_vertex2.x, m_vertex3.y - m_vertex2.y);
}

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
	double perimeterHalf = CTriangle::GetPerimeter() * 0.5;
	return std::round(100 * sqrt(perimeterHalf * (perimeterHalf - m_firstSide) * (perimeterHalf - m_secondSide) * (perimeterHalf - m_thirdSide))) / 100;
}

double CTriangle::GetPerimeter() const
{
	return m_firstSide + m_secondSide + m_thirdSide;
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

CRectangle::CRectangle(SPoint const & leftTopVertex, double const & width, double const & height, std::string const & outlineColor, std::string const & fillColor)
	:m_leftTopVertex(leftTopVertex),
	m_width(width),
	m_height(height),
	m_outlineColor(outlineColor),
	m_fillColor(fillColor)
{
	m_rightBottomVertex = {m_leftTopVertex.x + m_width, m_leftTopVertex.y + m_height};
}

SPoint CRectangle::GetLeftTop() const
{
	return m_leftTopVertex;
}

SPoint CRectangle::GetRightBottom() const
{
	return m_rightBottomVertex;
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
		<< "Right bottom vertex (" << m_rightBottomVertex.x << ", " << m_rightBottomVertex.y << ") "
		<< "Width = " << m_width << " "
		<< "Height = " << m_height << " "
		<< "Perimetr = " << CRectangle::GetPerimeter() << " "
		<< "Area = " << CRectangle::GetArea() << " "
		<< "Outline color = #" << CRectangle::GetOutlineColor() << " "
		<< "Fill color = #" << CRectangle::GetFillColor();

	return buffer.str();
}

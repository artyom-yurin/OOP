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

#include "stdafx.h"
#include "Shapes.h"

CTriangle::CTriangle(SPoint const & vertex1, SPoint const & vertex2, SPoint const & vertex3, std::string const & outlineColor, std::string const & fillColor)
	:m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	m_firstSide = std::round(1000 * std::hypot(m_vertex1.x - m_vertex2.x, m_vertex1.y - m_vertex2.y)) / 1000;
	m_secondSide = std::round(1000 * std::hypot(m_vertex1.x - m_vertex3.x, m_vertex1.y - m_vertex3.y)) / 1000;
	m_thirdSide = std::round(1000 * std::hypot(m_vertex3.x - m_vertex2.x, m_vertex3.y - m_vertex2.y)) / 1000;
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
	return 0.0;
}

double CTriangle::GetPerimeter() const
{
	return m_firstSide + m_secondSide + m_thirdSide;
}

std::string CTriangle::ToString() const
{
	return std::string();
}

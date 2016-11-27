#include "stdafx.h"
#include "LineSegment.h"

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

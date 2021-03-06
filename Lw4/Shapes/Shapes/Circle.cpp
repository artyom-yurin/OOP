#include "stdafx.h"
#include "Circle.h"

#define _USE_MATH_DEFINES
#include <math.h>

CCircle::CCircle(SPoint const & center, double const & radius, std::string const & outlineColor, std::string const & fillColor)
	: m_center(center),
	m_radius(radius)
{
	m_fillColor = fillColor;
	m_outlineColor = outlineColor;
}

SPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return M_PI * 2 * m_radius;
}

std::string CCircle::GetName() const
{
	return "circle";
}

std::string CCircle::GetSpecialInfo() const
{
	std::stringstream buffer;
	buffer << std::fixed << std::setprecision(2);
	buffer << "Center (" 
		<< m_center.x 
		<< ", " 
		<< m_center.y 
		<< ") "
		<< "Radius = "
		<< m_radius
		<< " Fill color = #"
		<< m_fillColor;

	return buffer.str();
}

#include "stdafx.h"
#include "Rectangle.h"


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
	return{ m_leftTopVertex.x + m_width, m_leftTopVertex.y + m_height };
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
#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle(SPoint const & leftTopVertex, double const & width, double const & height, std::string const & outlineColor, std::string const & fillColor)
	:m_leftTopVertex(leftTopVertex),
	m_width(width),
	m_height(height)
{
	m_fillColor = fillColor;
	m_outlineColor = outlineColor;
}

SPoint CRectangle::GetLeftTop() const
{
	return m_leftTopVertex;
}

SPoint CRectangle::GetRightBottom() const
{
	return{m_leftTopVertex.x + m_width, m_leftTopVertex.y + m_height};
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

std::string CRectangle::GetName() const
{
	return "rectangle";
}

std::string CRectangle::GetSpecialInfo() const
{
	std::stringstream buffer;
	buffer << std::fixed << std::setprecision(2);
	buffer << "Left top point ("
		<< m_leftTopVertex.x
		<< ", "
		<< m_leftTopVertex.y
		<< ") Right bottom point("
		<< GetRightBottom().x
		<< ", "
		<< GetRightBottom().y
		<< ") Width = "
		<< m_width
		<< " Height = "
		<< m_height
		<< " Fill color = #"
		<< m_fillColor;

	return buffer.str();
}

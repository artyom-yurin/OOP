#pragma once

#include "ISolidShape.h"

class CRectangle
	: public ISolidShape
{
public:
	CRectangle(SPoint const & leftTopVertex, double const & width, double const & height, std::string const & outlineColor, std::string const & fillColor);

	~CRectangle() = default;

	SPoint GetLeftTop() const;

	SPoint GetRightBottom() const;

	double GetWidth() const;

	double GetHeight() const;

	std::string GetFillColor() const override;

	std::string GetOutlineColor() const override;

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;
private:
	SPoint m_leftTopVertex;
	double m_width;
	double m_height;
	std::string m_outlineColor;
	std::string m_fillColor;
};
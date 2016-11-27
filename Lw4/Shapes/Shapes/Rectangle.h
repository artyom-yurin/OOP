#pragma once

#include "SolidShape.h"

class CRectangle
	: public CSolidShape
{
public:
	CRectangle(SPoint const & leftTopVertex, double const & width, double const & height, std::string const & outlineColor, std::string const & fillColor);

	~CRectangle() = default;

	SPoint GetLeftTop() const;

	SPoint GetRightBottom() const;

	double GetWidth() const;

	double GetHeight() const;

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string GetName() const override;

	std::string GetSpecialInfo() const override;
private:
	SPoint m_leftTopVertex;
	double m_width;
	double m_height;
};
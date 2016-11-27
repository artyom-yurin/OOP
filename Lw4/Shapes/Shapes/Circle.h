#pragma once

#include "ISolidShape.h"

class CCircle
	: public ISolidShape
{
public:
	CCircle(SPoint const & center, double const & radius, std::string const & outlineColor, std::string const & fillColor);

	~CCircle() = default;

	SPoint GetCenter() const;

	double GetRadius() const;

	std::string GetFillColor() const override;

	std::string GetOutlineColor() const override;

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;
private:
	SPoint m_center;
	double m_radius;
	std::string m_outlineColor;
	std::string m_fillColor;
};
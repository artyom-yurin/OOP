#pragma once

#include "SolidShape.h"

class CCircle
	: public CSolidShape
{
public:
	CCircle(SPoint const & center, double const & radius, std::string const & outlineColor, std::string const & fillColor);

	~CCircle() = default;

	SPoint GetCenter() const;

	double GetRadius() const;

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string GetName() const override;

	std::string GetSpecialInfo() const override;
private:
	SPoint m_center;
	double m_radius;
};
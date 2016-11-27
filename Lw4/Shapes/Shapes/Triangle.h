#pragma once
#include "ISolidShape.h"

class CTriangle
	: public ISolidShape
{
public:
	CTriangle(SPoint const & vertex1, SPoint const & vertex2, SPoint const & vertex3, std::string const & outlineColor, std::string const & fillColor);

	~CTriangle() = default;

	SPoint GetVertex1() const;

	SPoint GetVertex2() const;

	SPoint GetVertex3() const;

	std::string GetFillColor() const override;

	std::string GetOutlineColor() const override;

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

private:
	std::tuple<double, double, double> GetSides() const;
	SPoint m_vertex1;
	SPoint m_vertex2;
	SPoint m_vertex3;
	std::string m_outlineColor;
	std::string m_fillColor;
};

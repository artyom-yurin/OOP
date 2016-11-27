#pragma once
#include "SolidShape.h"

class CTriangle
	: public CSolidShape
{
public:
	CTriangle(SPoint const & vertex1, SPoint const & vertex2, SPoint const & vertex3, std::string const & outlineColor, std::string const & fillColor);

	~CTriangle() = default;

	SPoint GetVertex1() const;

	SPoint GetVertex2() const;

	SPoint GetVertex3() const;

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string GetName() const override;

	std::string GetSpecialInfo() const override;

private:
	std::tuple<double, double, double> GetSides() const;
	SPoint m_vertex1;
	SPoint m_vertex2;
	SPoint m_vertex3;
};

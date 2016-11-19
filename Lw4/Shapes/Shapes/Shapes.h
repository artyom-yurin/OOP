#pragma once

#include "ISolidShape.h"

struct SPoint
{
	double x;
	double y;
};

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
	SPoint m_vertex1;
	SPoint m_vertex2;
	SPoint m_vertex3;
	std::string m_outlineColor;
	std::string m_fillColor;
	double m_firstSide;
	double m_secondSide;
	double m_thirdSide;
};

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
	SPoint m_rightBottomVertex;
	double m_width;
	double m_height;
	std::string m_outlineColor;
	std::string m_fillColor;
};

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

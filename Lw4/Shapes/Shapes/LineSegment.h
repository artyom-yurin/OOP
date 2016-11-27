#pragma once

#include "Shape.h"

class CLineSegment
	: public CShape
{
public:
	CLineSegment(SPoint const & startPoint, SPoint const & endPoint, std::string const & outlineColor);

	~CLineSegment() = default;

	SPoint GetStartPoint() const;

	SPoint GetEndPoint() const;

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;
private:
	SPoint m_startPoint;
	SPoint m_endPoint;
};
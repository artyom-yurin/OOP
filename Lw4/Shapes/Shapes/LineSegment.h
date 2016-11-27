#pragma once

#include "ISolidShape.h"

class CLineSegment
	: public IShape
{
public:
	CLineSegment(SPoint const & startPoint, SPoint const & endPoint, std::string const & outlineColor);

	~CLineSegment() = default;

	SPoint GetStartPoint() const;

	SPoint GetEndPoint() const;

	std::string GetOutlineColor() const override;

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;
private:
	SPoint m_startPoint;
	SPoint m_endPoint;
	std::string m_outlineColor;
};
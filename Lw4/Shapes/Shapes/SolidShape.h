#pragma once

#include "Shape.h"
#include "ISolidShape.h"

class CSolidShape
	: public ISolidShape
	, public CShape
{
public:
	CSolidShape() = default;

	virtual ~CSolidShape() = default;

	std::string GetOutlineColor() const override;

	std::string GetFillColor() const override;
protected:
	std::string m_fillColor;
};


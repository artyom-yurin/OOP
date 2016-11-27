#pragma once

#include "Shape.h"
#include "ISolidShape.h"

class CSolidShape
	: public virtual ISolidShape
	, public virtual CShape
{
public:
	CSolidShape() = default;

	virtual ~CSolidShape() = default;

	std::string GetFillColor() const override;
protected:
	std::string m_fillColor;
};


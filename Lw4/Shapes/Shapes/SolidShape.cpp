#include "stdafx.h"
#include "SolidShape.h"

std::string CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}

std::string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

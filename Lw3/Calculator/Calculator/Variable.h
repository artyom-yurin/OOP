#pragma once
#include "Index.h"

class CVariable : public CIndex
{
public:
	CVariable() = default;

	CVariable(double value);

	~CVariable() = default;

	void SetValue(double value);
};


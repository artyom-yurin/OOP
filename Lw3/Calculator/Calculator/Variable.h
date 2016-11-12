#pragma once
#include "Index.h"

class CVariable : public CIndex
{
public:
	
	static std::shared_ptr<CVariable> Create();

	static std::shared_ptr<CVariable> Create(double value);

	~CVariable() = default;

	void SetValue(double value);

private:
	CVariable() = default;
	CVariable(double value);
};

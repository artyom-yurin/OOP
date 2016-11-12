#pragma once
#include "Index.h"
#include "Function.h"

class CVariable : public CIndex
{
public:
	
	static std::shared_ptr<CVariable> Create();

	static std::shared_ptr<CVariable> Create(double value);

	~CVariable() = default;

	void SetValue(double value);

	void AddFunction(std::shared_ptr<CFunction> & pFunction);

private:
	CVariable() = default;

	CVariable(double value);
	
	std::vector<std::shared_ptr<CFunction>> functions;
};

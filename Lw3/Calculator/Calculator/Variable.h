#pragma once
#include "Index.h"

class CFunction;

class CVariable : public CIndex
{
public:
	
	static std::shared_ptr<CVariable> Create();

	static std::shared_ptr<CVariable> Create(double value);

	~CVariable() = default;

	void SetValue(double value);

	void AddDependentFunction(std::shared_ptr<CFunction> const & pFunction);

	CVariable() = default;

	CVariable(double value);
private:

	std::vector<std::shared_ptr<CFunction>> m_dependentFunctions;
};

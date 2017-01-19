#pragma once

#include "Index.h"

class CVariable;

enum class Sign
{
	plus,
	minus,
	factor,
	divider
};

class CFunction : public CIndex
{
public:
	static std::shared_ptr<CFunction> Create(std::shared_ptr<CIndex> const & index);

	static std::shared_ptr<CFunction> Create(std::shared_ptr<CIndex> const & firstIndex, Sign sign, std::shared_ptr<CIndex> const & secondIndex);

	~CFunction() = default;

	void AddDependentVariables(std::vector<std::shared_ptr<CVariable>> const & dependentVariables);

	std::vector<std::shared_ptr<CVariable>> & GetDependentVariables();

	void Refresh();

	CFunction(std::shared_ptr<CIndex> const & index);

	CFunction(std::shared_ptr<CIndex> const & firstIndex, Sign sign, std::shared_ptr<CIndex> const & secondIndex);

	void Clear();

private:

	std::shared_ptr<CIndex> m_firstIndex = nullptr;

	Sign m_sign;

	std::shared_ptr<CIndex> m_secondIndex = nullptr;

	std::vector<std::shared_ptr<CVariable>> m_dependentVariables;
};


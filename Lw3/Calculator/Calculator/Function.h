#pragma once

#include "Index.h"

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
	CFunction(const std::shared_ptr<CIndex> & index);

	CFunction(std::shared_ptr<CIndex> firstIndex, Sign sign, std::shared_ptr<CIndex> secondIndex);

	~CFunction() = default;

	void Refresh();
private:
	std::shared_ptr<CIndex> m_firstIndex = nullptr;
	Sign m_sign;
	std::shared_ptr<CIndex> m_secondIndex = nullptr;
};


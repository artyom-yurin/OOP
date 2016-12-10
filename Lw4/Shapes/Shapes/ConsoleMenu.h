#pragma once

#include "Shape.h"

class CConsoleMenu
{
public:
	CConsoleMenu() = default;

	~CConsoleMenu() = default;

	void RunCommand(std::istream & stream);
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};


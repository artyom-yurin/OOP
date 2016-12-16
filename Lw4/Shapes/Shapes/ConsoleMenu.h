#pragma once

#include "Shape.h"

class CConsoleMenu
{
public:
	CConsoleMenu() = default;

	~CConsoleMenu() = default;

	void RunCommand(std::istream & stream, std::ostream & output);
private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};


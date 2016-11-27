#pragma once

struct SPoint
{
	double x;
	double y;
};

class IShape
{
public:
	IShape() = default;

	virtual ~IShape() = default;

	virtual double GetArea() const = 0;

	virtual double GetPerimeter() const = 0;

	virtual std::string GetName() const = 0;

	virtual std::string GetSpecialInfo() const = 0;

	virtual std::string GetOutlineColor() const = 0;
};


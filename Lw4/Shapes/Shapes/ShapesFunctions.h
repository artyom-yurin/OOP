#pragma once

std::shared_ptr<IShape> GetLargeAreaShape(std::vector<std::shared_ptr<IShape>> const & shapes);

std::shared_ptr<IShape> GetSmallPerimeterShape(std::vector<std::shared_ptr<IShape>> const & shapes);

bool IsColorCorrect(std::string const & color);

void RectangleCommand(std::istream & stream, std::ostream & output, std::vector<std::shared_ptr<IShape>> & shapes);

void TriangleCommand(std::istream & stream, std::ostream & output, std::vector<std::shared_ptr<IShape>> & shapes);

void CircleCommand(std::istream & stream, std::ostream & output, std::vector<std::shared_ptr<IShape>> & shapes);

void LineCommand(std::istream & stream, std::ostream & output, std::vector<std::shared_ptr<IShape>> & shapes);

std::string ToString(std::shared_ptr<IShape> const & shape);
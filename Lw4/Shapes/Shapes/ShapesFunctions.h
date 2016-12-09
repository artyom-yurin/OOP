#pragma once

std::shared_ptr<CShape> GetLargeAreaShape(std::vector<std::shared_ptr<CShape>> const & shapes);

std::shared_ptr<CShape> GetSmallPerimeterShape(std::vector<std::shared_ptr<CShape>> const & shapes);

bool CorrectColor(std::string const & color);

void RectangleCommand(std::istream & stream, std::vector<std::shared_ptr<CShape>> & shapes);

void TriangleCommand(std::istream & stream, std::vector<std::shared_ptr<CShape>> & shapes);

void CircleCommand(std::istream & stream, std::vector<std::shared_ptr<CShape>> & shapes);

void LineCommand(std::istream & stream, std::vector<std::shared_ptr<CShape>> & shapes);

std::string ToString(std::shared_ptr<CShape> const & shape);
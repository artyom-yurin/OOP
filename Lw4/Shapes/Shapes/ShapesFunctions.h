#pragma once

std::shared_ptr<IShape> GetLargeAreaShape(std::vector<std::shared_ptr<IShape>> const & shapes);

std::shared_ptr<IShape> GetSmallPerimeterShape(std::vector<std::shared_ptr<IShape>> const & shapes);

bool CorrectColor(std::string const & color);
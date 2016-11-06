#pragma once

std::vector <double> GetNumbers(std::istream & input);

double GetMultiplier(const std::vector <double> & numbers);

void ProcessVector(std::vector <double> & numbers);

void PrintVector(std::ostream & output, const std::vector <double> & numbers);

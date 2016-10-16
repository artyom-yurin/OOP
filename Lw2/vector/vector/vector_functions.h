#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <iterator>

std::vector <double> GetNumbers(std::istream & input);

auto GetMaxMinElement(const std::vector <double> & numbers);

double GetMultiplier(const std::vector <double> & numbers);

void ProcessVector(std::vector <double> & numbers);

void PrintVector(std::ostream & output, const std::vector <double> & numbers);
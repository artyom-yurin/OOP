#pragma once

#include <vector>

template < typename T, typename Less = std::less<T>>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less = Less())
{
	if (arr.empty())
	{
		return false;
	}
	auto max = arr.cbegin();

	for (auto it = arr.cbegin(); it < arr.cend(); ++it)
	{
		if (less(*max, *it))
		{
			max = it;
		}
	}
	maxValue = *max;
	return true;
}
#include "utils.h"

std::mt19937 gen{ std::random_device{}() };

ulint nextPowerOf2(ulint n)
{
	ulint p = 1;
	if (n && !(n & (n - 1)))
		return n;

	while (p < n)
		p <<= 1;

	return p;
}
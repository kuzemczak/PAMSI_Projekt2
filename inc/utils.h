#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "randutils.hpp"

#define INDEX_OUT_OF_BOUNDS 1

typedef unsigned int ulint;

#define INF (ulint)1000000000

template<typename T>
void Swap(T & v0, T & v1)
{
	T tmp = v0;
	v0 = v1;
	v1 = tmp;
}

ulint nextPowerOf2(ulint n);
extern std::mt19937 gen;

template<typename T>
T random(T min, T max) {
	return std::uniform_int_distribution<T>{min, max}(gen);
}

#endif

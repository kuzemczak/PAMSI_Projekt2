#ifndef UTILS_H
#define UTILS_H

#include <iostream>

#define INDEX_OUT_OF_BOUNDS 1

typedef unsigned int ulint;

template<typename T>
void Swap(T & v0, T & v1)
{
	T tmp = v0;
	v0 = v1;
	v1 = tmp;
}

#endif

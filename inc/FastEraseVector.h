#ifndef FASTERASEVECTOR_H
#define FASTERASEVECTOR_H

#include "utils.h"
#include "Vector.h"

// Struktura danych pozwalajaca na szybkie usuwanie elementow
// kosztem ich pomieszania
template<typename T>
class FastEraseVector : public Vector<T>
{
	using Vector<T>::data;
	using Vector<T>::size_;
public:
	using Vector<T>::pop_back;
	using Vector<T>::size;
	T erase(ulint index);
};

template<typename T>
T FastEraseVector<T>::erase(ulint index)
{
	Swap(data[index], data[size_ - 1]);
	return pop_back();
}
#endif


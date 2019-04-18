#ifndef VECTOR_H
#define VECTOR_H

#include "utils.h"

template<typename T>
class Vector 
{
protected:
	ulint alloc_size;
	ulint size_;
public:
	T * data;

//public:
	Vector();
	~Vector();

	void alloc_more();
	void alloc_less();

	T & operator[](ulint i);
	const T & operator[](ulint i) const;
	void push_back(T element);
	T pop_back();
	void insert(ulint i, T element);
	void erase(ulint i);
	const ulint size() const;
};

template<typename T>
Vector<T>::Vector()
{
	alloc_size = 1;
	data = new T[alloc_size];
	size_ = 0;
}

template<typename T>
Vector<T>::~Vector()
{
	for (int i = 0; i < size_; i++)
	{
		delete &(data[i]);
	}

	free(data);
}

template<typename T>
void Vector<T>::alloc_more()
{
	T * tmp = data;
	alloc_size *= 2;
	data = static_cast<T*>(malloc(alloc_size * sizeof(T)));
	memcpy(data, tmp, size_ * sizeof(T));
	free(tmp);
}

template<typename T>
void Vector<T>::alloc_less()
{
	T * tmp = data;
	alloc_size /= 2;
	data = static_cast<T*>(malloc(alloc_size * sizeof(T)));
	memcpy(data, tmp, size_ * sizeof(T));
	free(tmp);
}

template<typename T>
T & Vector<T>::operator[](ulint i)
{
	return data[i];
}

template<typename T>
const T & Vector<T>::operator[](ulint i) const
{
	return data[i];
}

template<typename T>
void Vector<T>::push_back(T element)
{
	if (++size_ > alloc_size)
		alloc_more();

	data[size_ - 1] = element;
}

template<typename T>
T Vector<T>::pop_back()
{
	if (size_ == 0)
		throw 2;

	T ret = data[--size_];

	if (size_ < alloc_size / 2)
		alloc_less();

	return ret;
}

template<typename T>
void Vector<T>::insert(ulint i, T element)
{
	if (++size_ > alloc_size)
		alloc_more();

	for (ulint j = size_ - 1; j > i; j--)
	{
		data[j] = data[j - 1];
	}

	data[i] = element;
}

template<typename T>
void Vector<T>::erase(ulint i)
{
	for (ulint j = i; j < size_ - 1; j++)
	{
		data[j] = data[j + 1];
	}

	if (--size_ < alloc_size / 2)
		alloc_less();
}

template<typename T>
const ulint Vector<T>::size() const
{
	return size_;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const Vector<T>& v) {
	out << '[';

	for (ulint i = 0; i < v.size(); i++)
		out << v[i] << ", ";

	out << "\b\b]";
	
	return out;
}

#endif
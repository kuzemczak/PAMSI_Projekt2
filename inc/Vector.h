#ifndef VECTOR_H
#define VECTOR_H

#include "utils.h"

template<typename T>
class vector_iterator
{
	T * ptr;

public:

	vector_iterator() { ptr = NULL; }
	vector_iterator(T * elem_ptr) { ptr = elem_ptr; }

	~vector_iterator() {}

	vector_iterator<T> operator++ (int) { vector_iterator<T> tmp = *this; ptr++; return tmp; }
	vector_iterator<T> operator++ () { ptr++; return *this; }
	vector_iterator<T> operator+ (ulint offset) { ptr += offset; return *this; }
	vector_iterator<T> operator+= (ulint offset) { return *this = *this + offset; }
	T & operator* () { return *ptr; }
	bool operator== (vector_iterator<T> it) { return ptr == it.ptr; }
	bool operator!= (vector_iterator<T> it) { return ptr != it.ptr; }
};

template<typename T>
class Vector 
{
	static int cntr; //debug
protected:
	ulint alloc_size;
	ulint size_;
public:
	int number;
	T * data;

	Vector(ulint size = 0);
	~Vector();
	Vector<T> & operator= (const Vector<T> & v);

	void alloc_more();
	void alloc_less();

	T & operator[](ulint i);
	const T & operator[](ulint i) const;
	void push_back(T element);
	T pop_back();
	void insert(ulint i, T element);
	void erase(ulint i);
	const ulint size() const;

	//vector_iterator<T> begin();
	const vector_iterator<T> begin() const;
	const vector_iterator<T> end() const;
};

template<typename T>
int Vector<T>::cntr = 0;

template<typename T>
Vector<T>::Vector(ulint size) : size_(size)
{
	number = cntr++;
	if (size > 0)
	{
		alloc_size = nextPowerOf2(size);
		data = new T[alloc_size];
	}
	else
	{
		alloc_size = 1;
		data = new T[alloc_size];
	}
}

template<typename T>
Vector<T>::~Vector()
{
	if (data != NULL)
	{
		delete[] data;
	}
}

template <typename T>
Vector<T> & Vector<T>::operator= (const Vector<T> & v)
{
	if (data != NULL)
	{
		delete[] data;
	}

	size_ = v.size_;
	alloc_size = v.alloc_size;
	data = new T[alloc_size];
	for (ulint i = 0; i < size_; i++)
	{
		data[i] = v.data[i];
	}

	return *this;
}

template<typename T>
void Vector<T>::alloc_more()
{
	alloc_size *= 2;
	if (data != NULL)
	{
		T * tmp = data;
		data = new T[alloc_size];
		for (ulint i = 0; i < size_; i++)
			data[i] = tmp[i];
		delete[] tmp;
	}
	else
	{
		data = new T[alloc_size];
	}
}

template<typename T>
void Vector<T>::alloc_less()
{
	T * tmp = data;
	alloc_size /= 2;
	data = new T[alloc_size];
	for (ulint i = 0; i < size_; i++)
		data[i] = tmp[i];
	delete[] tmp;
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
	if (size_ + 1> alloc_size)
		alloc_more();
	data[size_++] = element;
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
	if (size_ + 1> alloc_size)
		alloc_more();

	size_++;

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
const vector_iterator<T> Vector<T>::begin() const
{
	return vector_iterator<T>(data);
}

template <typename T>
const vector_iterator<T> Vector<T>::end() const
{
	return vector_iterator<T>(data + size_);
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
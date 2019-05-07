#ifndef LIST_H
#define LIST_H

#include "utils.h"

// element listy
template<typename T>
class list_elem 
{
public:
	// wskaznik na nastepny element listy
	list_elem<T> * next;

	// zawartosc elementu
	T data;

	list_elem(T dat) : 
		data(dat), 
		next(NULL) {}
	list_elem(T dat, list_elem<T> * nxt) : 
		data(dat),
		next(nxt) {}
};

// iterator listy
template<typename T>
class list_iterator
{
	// wskaznik na element listy w obecnej iteracji
	list_elem<T> * ptr;

public:
	list_iterator() { ptr = NULL; }
	list_iterator(list_elem<T> * elem_ptr) { ptr = elem_ptr; }
	~list_iterator() {}

	list_iterator<T> operator++ (int) { list_iterator<T> tmp = *this; ptr = ptr->next; return tmp; }
	list_iterator<T> operator++ () { ptr = ptr->next; return *this; }
	list_iterator<T> operator+ (ulint offset) 
	{ 
		list_elem<T> * tmp = ptr;
		for (int i = 0; i < offset; i++)
			tmp = tmp->next;
		return list_iterator<T>(tmp);
	}
	list_iterator<T> operator+= (ulint offset) { return *this = *this + offset; }
	T & operator* () { return ptr->data; }
	bool operator== (list_iterator<T> it) { return ptr == it.ptr; }
	bool operator!= (list_iterator<T> it) { return ptr != it.ptr; }
};

// Lista jednokierunkowa
template<typename T>
class List
{
	// pierwszy element listy
	list_elem<T>* first;

	// wielkosc listy
	ulint list_size;

public:
	List() { first = NULL; list_size = 0; }
	~List();

	void push_front(T elem);
	T pop();
	T erase(ulint i);
	void insert(ulint i, T elem);

	ulint size();
	list_iterator<T> begin();
	list_iterator<T> end();

	T & operator[](ulint i);

};

template<typename T>
List<T>::~List()
{
	list_elem<T> *tmp;
	list_elem<T> *next;
	tmp = first;
	for (ulint i = 0; i < list_size; i++)
	{
		next = tmp->next;
		delete tmp;
		tmp = next;
	}
}

template<typename T>
void List<T>::push_front(T elem)
{
	list_elem<T> * newElem = new list_elem<T>(elem, first);
	first = newElem;
	list_size++;
}

template<typename T>
T List<T>::pop()
{
	if (list_size > 0)
	{
		list_elem<T> * tmp = first;
		T ret = first->data;
		first = tmp->next;
		delete tmp;
		list_size--;
		return ret;
	}
	else
		throw INDEX_OUT_OF_BOUNDS;

	return 0;
}
template<typename T>
T List<T>::erase(ulint i)
{
	if (i >= 0 && i < list_size)
	{
		list_elem<T> * tmp = NULL;
		list_elem<T> ** prev = &first;
		T ret;

		for (ulint j = 0; j < i; j++)
		{
			prev = &((*prev)->next);
		}

		tmp = *prev;
		*prev = (*prev)->next;
		ret = tmp->data;
		delete tmp;
		list_size--;
		return ret;
	}
	else
		throw INDEX_OUT_OF_BOUNDS;

	return 0;
}

template<typename T>
void List<T>::insert(ulint i, T elem)
{
	if (i >= 0 && i <= list_size)
	{
		list_elem<T> * tmp = new list_elem<T>;
		tmp->data = elem;
		list_elem<T> ** prev = &first;

		for (ulint j = 0; j < i; j++)
		{
			prev = &((*prev)->next);
		}

		tmp->next = *prev;
		*prev = tmp;
		list_size++;
	}
	else
		throw INDEX_OUT_OF_BOUNDS;
}

template<typename T>
T & List<T>::operator[](ulint i)
{
	if (i >= list_size || i < 0)
		throw INDEX_OUT_OF_BOUNDS;

	list_elem<T> * e = first;
	for (ulint j = 0; j < list_size; j++)
	{
		if (j == i)
			return e->data;

		e = e->next;
	}

	return first->data;
}

template<typename T>
ulint List<T>::size()
{
	return list_size;
}

template<typename T>
list_iterator<T> List<T>::begin()
{
	return list_iterator<T>(first);
}

template<typename T>
list_iterator<T> List<T>::end()
{
	return list_iterator<T>(NULL);
}

template <typename T>
std::ostream& operator<< (std::ostream& out, List<T> v) 
{
	out << '[';

	for (list_iterator<T> i = v.begin(); i != v.end(); i++)
	{
		out << *i << ", ";
	}

	out << "\b\b]";
	return out;
}

#endif
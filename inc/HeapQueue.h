#ifndef HEAPQUEUE_H
#define HEAPQUEUE_H

#include <functional>


#include "Vector.h"
#include "utils.h"

// Klasa - element kolejki priorytetowej
template<typename T>
class QueueItem
{
public:
	// klucz wg. ktorego oceniany jest priorytet
	ulint key;
	
	// zawartosc elementu
	T data;

	QueueItem(int k = 0) :
		key(k) {}
	QueueItem(T dat, int k = 0) :
		key(k),
		data(dat) {}
};

// Kolejka priorytetowa w postaci kopca
template<typename T>
class HeapQueue : public Vector<QueueItem<T>>
{
	// funkcja porownujaca dwa elementy,
	// wg ktorej budowany jest kopiec
	bool(*comparator)(QueueItem<T>, QueueItem<T>);

	using Vector<QueueItem<T>>::size_;
	using Vector<QueueItem<T>>::alloc_size;
	using Vector<QueueItem<T>>::data;
public:
	HeapQueue();
	HeapQueue(bool(*cmp)(QueueItem<T>, QueueItem<T>));
	~HeapQueue() {}

	using Vector<QueueItem<T>>::pop_back;
	using Vector<QueueItem<T>>::push_back;

	// odbudowanie kopca przesuwajac element w gore
	ulint reheap_item_up(ulint index);

	// odbudowanie kopca przesuwajac element w dol
	ulint reheap_item_down(ulint index);

	// zdjecie elementu ze szczytu kopca
	T pop_front();

	// wepchniecie elementu na kopiec
	// i odbudowanie kopca
	// zwraca indeks elementu po odbudowaniu
	ulint push(T element, ulint key = 0);

	// ustawienie klucza wskazanego elementu
	// i odbudowanie kopca
	ulint set_item_key(ulint index, ulint newKey);

	// uzyskanei zawartosci wskazanego elementu
	T & operator [] (ulint index);

	// uzyskanie klucza wskazanego elementu
	ulint get_key(ulint index);

	bool contains(T element);
};

template<typename T>
HeapQueue<T>::HeapQueue()
{
	comparator = [](QueueItem<T> i0, QueueItem<T> i1) { return i0.key < i1.key; };
}

template<typename T>
HeapQueue<T>::HeapQueue(bool(*cmp)(QueueItem<T>, QueueItem<T>))
{
	comparator = cmp;
}

template<typename T>
ulint HeapQueue<T>::reheap_item_up(ulint index)
{
	// indeks elementu i jego rodzica
	int el_index = index, parent_index;

	// przesuwanie elementu w gore dopoki kopiec
	// nie bedzie odbudowany
	while (el_index > 0)
	{
		parent_index = (el_index - 1) / 2;

		if (comparator(data[el_index], data[parent_index]))
		{
			Swap(data[el_index], data[parent_index]);
			el_index = parent_index;
			parent_index = (el_index - 1) / 2;
		}
		else
			break;
	}

	return el_index;
}

template<typename T>
ulint HeapQueue<T>::reheap_item_down(ulint index)
{
	// el_index - galaz wyzsza, k, m - galaz nizsza
	int el_index = index, k = 2 * el_index + 1, m;

	while (k < size_)
	{
		// decyzja: lewa czy prawa odnoga?
		if (k + 1 < size_ && comparator(data[k + 1], data[k]))
			m = k + 1;
		else
			m = k;

		// jesli jest nizej mniejszy element,
		// to zamiana miejscami wyzszego z nizszym.
		if (comparator(data[m], data[el_index]))
		{
			Swap(data[el_index], data[m]);
			el_index = m;
			k = 2 * el_index + 1;
		}
		else
			break;
	}

	return el_index;
}

template<typename T>
T HeapQueue<T>::pop_front()
{
	Swap(data[0], data[size_ - 1]);
	T ret = pop_back().data;
	reheap_item_down(0);
	
	return ret;
}

template<typename T>
ulint HeapQueue<T>::push(T element, ulint key)
{
	push_back(QueueItem<T>(element, key));

	return reheap_item_up(size_ - 1);
}

template<typename T>
ulint HeapQueue<T>::set_item_key(ulint index, ulint newKey)
{
	data[index].key = newKey;
	ulint ret = reheap_item_up(index);
	if (ret == index)
		ret = reheap_item_down(index);
	return ret;
}

template<typename T>
T & HeapQueue<T>::operator [] (ulint index)
{
	return data[index].data;
}

template<typename T>
ulint HeapQueue<T>::get_key(ulint index)
{
	return data[index].key;
}

template<typename T>
bool HeapQueue<T>::contains(T element)
{
	for (int i = 0; i < size_; i++)
		if (element == data[i].data)
			return true;
	return false;
}

#endif

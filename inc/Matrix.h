#ifndef MATRIX_H
#define MATRIX_H

#include "dataStruct.h"

template <typename T>
class Matrix
{
	ulint num_rows, num_cols;

	T **data;
public:
	Matrix(ulint rws, ulint cls);
	~Matrix();

	T* operator[](ulint row);
	const T* operator[](ulint row) const;
	ulint rows();
	ulint cols();
	const ulint rows() const; 
	const ulint cols() const;
};

template<typename T>
Matrix<T>::Matrix(ulint rws, ulint cls)
{
	num_rows = rws;
	num_cols = cls;
	data = new T*[num_rows];
	for (ulint i = 0; i < num_rows; i++)
	{
		data[i] = new T[num_cols];
	}
}

template<typename T>
Matrix<T>::~Matrix()
{
	for (ulint i = 0; i < num_rows; i++)
	{
		delete [] data[i];
	}
	delete [] data;
}

template<typename T>
T * Matrix<T>::operator[](ulint row)
{
	return data[row];
}

template<typename T>
const T * Matrix<T>::operator[](ulint row) const
{
	return data[row];
}

template<typename T>
ulint Matrix<T>::rows()
{
	return num_rows;
}

template<typename T>
ulint Matrix<T>::cols()
{
	return num_cols;
}

template<typename T>
const ulint Matrix<T>::rows() const
{
	return num_rows;
}

template<typename T>
const ulint Matrix<T>::cols() const
{
	return num_cols;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const Matrix<T>& v) {
	out << '[';

	for (ulint i = 0; i < v.rows(); i++)
	{
		out << "\t";
		for(ulint j = 0; j < v.cols(); j++)
			out << v[i][j] << ", ";
		if(i < v.rows() - 1)
			out << "\n";
	}

	out << "\b\b]";
	
	return out;
}

#endif
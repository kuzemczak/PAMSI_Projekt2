#ifndef MATRIX_H
#define MATRIX_H

#include "utils.h"
#include "Vector.h"

template <typename T>
class Matrix
{
	ulint num_rows, num_cols;

	Vector<Vector<T>> *data;
public:
	Matrix(ulint rws, ulint cls);
	~Matrix();

	Vector<T>& operator[](ulint row);
	const Vector<T>& operator[](ulint row) const;
	ulint rows();
	ulint cols();
	const ulint rows() const; 
	const ulint cols() const;

	void zeros();
};

template<typename T>
Matrix<T>::Matrix(ulint rws, ulint cls)
{
	num_rows = rws;
	num_cols = cls;
	
	data = new Vector<Vector<T>>(rws);
	for (Vector <T> & v : *data)
		v = Vector<T>(cls);
}

template<typename T>
Matrix<T>::~Matrix()
{
	delete data;
}

template<typename T>
Vector<T> & Matrix<T>::operator[](ulint row)
{
	return (*data)[row];
}

template<typename T>
const Vector<T> & Matrix<T>::operator[](ulint row) const
{
	return (*data)[row];
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

template<typename T>
void Matrix<T>::zeros()
{
	for (Vector<T> & v0 : *data)
		for (T & v1 : v0)
			v1 = 0;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const Matrix<T>& v) {
	out << '[';

	for (ulint i = 0; i < v.rows(); i++)
	{
		out << " ";
		for(ulint j = 0; j < v.cols(); j++)
			out << v[i][j] << ", ";
		if(i < v.rows() - 1)
			out << "\n ";
	}

	out << "\b\b]";
	
	return out;
}

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:17:41 by pablo             #+#    #+#             */
/*   Updated: 2026/05/04 20:56:09 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>

#ifndef ARRAY_TPP
#define ARRAY_TPP

/////////////////////////////////// ORTHODOX ///////////////////////////////////

template <typename T> Array<T>::Array() : _elements(NULL), _size(0) {}

template <typename T>
Array<T>::Array(const Array<T> &copy)
	: _elements(copy._size ? new T[copy._size]() : NULL), _size(copy._size)
{
	for (size_t i = 0; i < _size; i++)
		_elements[i] = copy._elements[i];
}

template <typename T> Array<T> &Array<T>::operator=(const Array<T> &src)
{
	if (this != &src)
	{
		if (_size != src._size)
		{
			delete[] _elements;
			_elements = new T[src._size]();
			_size = src._size;
		}

		for (size_t i = 0; i < _size; i++)
			_elements[i] = src._elements[i];
	}

	return *this;
}

template <typename T> Array<T>::~Array()
{
	delete[] _elements;
}

///////////////////////////////// CONSTRUCTORS /////////////////////////////////

template <typename T>
Array<T>::Array(unsigned int size) : _elements(new T[size]()), _size(size)
{
}

/////////////////////////////////// OPERATORS //////////////////////////////////
template <typename T>
T& Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw std::out_of_range("Array: index out of range");
	return _elements[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw std::out_of_range("Array: index out of range");
	return _elements[index];
}

//////////////////////////////////// MEMBERS ///////////////////////////////////
template <typename T>
size_t Array<T>::size() const
{
	return _size;
}

#endif

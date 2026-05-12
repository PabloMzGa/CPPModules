/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 18:42:10 by pabmart2          #+#    #+#             */
/*   Updated: 2026/05/12 19:33:00 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <algorithm>
#include <climits>

/////////////////////////////////// ORTHODOX ///////////////////////////////////

Span::Span() : _size(0)
{
}

Span::Span(Span &src) : _size(src._size), _vector(std::vector<int>(src._vector))
{
}

Span &Span::operator=(Span &src)
{
	this->_size = src._size;
	this->_vector = std::vector<int>(src._vector);
	return (*this);
}

Span::~Span()
{
}

///////////////////////////////// CONSTRUCTORS /////////////////////////////////

Span::Span(std::size_t size)
{
	this->_size = size;
	this->_vector = std::vector<int>();
	this->_vector.reserve(size);
}

/////////////////////////////////// MEMBERS ////////////////////////////////////

void Span::addNumber(int number)
{
	if (_vector.size() >= _size)
		throw std::runtime_error("No space enough in Span");
	else
		_vector.push_back(number);
}

unsigned int Span::shortestSpan()
{
	unsigned int	minSpan;
	int				diff;

	if (_vector.size() < 2)
		throw std::runtime_error("Not enough numbers");
	std::vector<int> tmp = _vector;
	std::sort(tmp.begin(), tmp.end());
	minSpan = tmp[1] - tmp[0];
	for (size_t i = 2; i < tmp.size(); i++)
	{
		diff = tmp[i] - tmp[i - 1];
		if ((unsigned int)diff < minSpan)
			minSpan = diff;
	}
	return (minSpan);
}

unsigned int Span::longestSpan()
{
	int	min;
	int	max;

	min = *std::min_element(_vector.begin(), _vector.end());
	max = *std::max_element(_vector.begin(), _vector.end());
	return (max - min);
}

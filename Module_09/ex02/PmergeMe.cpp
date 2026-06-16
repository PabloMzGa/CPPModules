/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:28:27 by pablo             #+#    #+#             */
/*   Updated: 2026/06/17 01:02:17 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// ORTHODOX ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src)
    : _vector(src._vector), _deque(src._deque)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
	if (this != &src)
	{
		this->_vector = src._vector;
		this->_deque = src._deque;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// HELPERS ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

unsigned int PmergeMe::parse_positive_int(const std::string &token)
{
	if (token.empty())
		throw std::runtime_error("Error: empty token");
	for (std::string::size_type i = 0; i < token.size(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(token[i])))
			throw std::runtime_error(std::string("Error: invalid token '") +
			                         token + "'");
	}
	std::stringstream ss(token);
	unsigned long value = 0;
	char extra = '\0';
	if (!(ss >> value) || (ss >> extra))
		throw std::runtime_error(std::string("Error: invalid token '") + token +
		                         "'");
	if (value > std::numeric_limits<unsigned int>::max())
		throw std::runtime_error(std::string("Error: number out of range: '") +
		                         token + "'");
	return static_cast<unsigned int>(value);
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CONSTRUCTORS /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

PmergeMe::PmergeMe(const std::string &input)
{
	clock_t start;
	clock_t end;

	start = clock();
	load_values(input, _vector);
	end = clock();
	_vector_time_ms =
	    static_cast<double>(end - start) * 1000.0 / CLOCKS_PER_SEC;

	start = clock();
	load_values(input, _deque);
	end = clock();
	_deque_time_ms = static_cast<double>(end - start) * 1000.0 / CLOCKS_PER_SEC;

	start = clock();
	load_values(input, _list);
	end = clock();
	_list_time_ms = static_cast<double>(end - start) * 1000.0 / CLOCKS_PER_SEC;
}

void PmergeMe::sort()
{
	clock_t start;
	clock_t end;
	std::cout << "Before: ";
	print_container(_vector);
	std::cout << std::endl;

	start = clock();
	apply_order(_vector, ford_johson::ford_johnson(_vector));
	end = clock();
	_vector_time_ms +=
	    static_cast<double>(end - start) * 1000.0 / CLOCKS_PER_SEC;

	start = clock();
	apply_order(_deque, ford_johson::ford_johnson(_deque));
	end = clock();
	_deque_time_ms +=
	    static_cast<double>(end - start) * 1000.0 / CLOCKS_PER_SEC;

	start = clock();
	apply_order(_list, ford_johson::ford_johnson(_list));
	end = clock();
	_list_time_ms += static_cast<double>(end - start) * 1000.0 / CLOCKS_PER_SEC;

	std::cout << "After: ";
	print_container(_list);
	std::cout << std::endl;

	std::cout << "Time to process a range of " << _vector.size()
	          << " elements with std::vector : " << _vector_time_ms << " ms"
	          << std::endl;

	std::cout << "Time to process a range of " << _deque.size()
	          << " elements with std::deque : " << _deque_time_ms << " ms"
	          << std::endl;

	std::cout << "Time to process a range of " << _list.size()
	          << " elements with std::list : " << _list_time_ms << " ms"
	          << std::endl;
}

namespace ford_johson
{
s_JacobsthalSeq build_jacobsthal_seq(std::size_t size)
{
	std::size_t jn;
	s_JacobsthalSeq js;
	js.size = 0;
	for (size_t n = 2; n < 64; n++)
	{
		jn = ((1LL << (n + 1)) + (n % 2 == 0 ? 1 : -1)) / 3;
		if (jn > size)
			break;
		js.seq[js.size++] = jn - 1; // Make sequence 0 based
	}
	return js;
}
} // namespace ford_johson

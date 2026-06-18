/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:28:27 by pablo             #+#    #+#             */
/*   Updated: 2026/06/18 20:18:10 by pabmart2         ###   ########.fr       */
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

/**
 * @brief Parses a string token as a strictly positive unsigned integer.
 *
 * Validates that the token contains only decimal digits, converts it to an
 * unsigned long, checks for trailing characters, and verifies that the value
 * fits within the range of `unsigned int`. Any malformed or out‑of‑range
 * token results in a `std::runtime_error`.
 *
 * @param token  String representing the integer to parse.
 *
 * @return The parsed value as an unsigned int.
 *
 * @throws std::runtime_error If the token is empty, contains non‑digit
 *         characters, includes trailing data, or represents a value outside
 *         the range of `unsigned int`.
 */
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

/**
 * @brief Constructs a PmergeMe instance by parsing and loading input values
 *        into all internal containers while measuring load times.
 *
 * Parses the whitespace‑separated integers contained in `input` and loads
 * them into the internal `std::vector`, `std::deque`, and `std::list`.
 * Each container is populated independently using `load_values()`, and the
 * time required to fill each one is measured in milliseconds.
 *
 * @param input  String containing the integer sequence to load.
 *
 * @throws std::runtime_error If the input contains no valid numbers.
 */
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

/**
 * @brief Sorts the stored containers using the Ford–Johnson algorithm and
 *        measures execution times.
 *
 * Prints the initial state of the list, sorts the internal `std::vector`,
 * `std::deque`, and `std::list` using the Ford–Johnson algorithm, and
 * measures the time taken for each container type. After sorting, the
 * function prints the resulting list and reports the processing time for
 * each container.
 *
 * @note The function uses `apply_order()` to rebuild each container from the
 *       sorted iterator array returned by the Ford–Johnson procedure.
 *
 * @throws std::runtime_error If any parsing or ordering step fails internally.
 */
void PmergeMe::sort()
{
	clock_t start;
	clock_t end;
	std::cout << "Before: ";
	print_container(_list, 4);

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
	print_container(_list, 4);

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
	namespace utils
	{

		structs::s_JacobsthalSeq build_jacobsthal_seq(std::size_t size)
		{
			std::size_t jn;
			structs::s_JacobsthalSeq js;
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
	}
} // namespace ford_johson

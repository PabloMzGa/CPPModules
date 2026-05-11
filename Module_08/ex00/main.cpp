/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:35:50 by pabmart2          #+#    #+#             */
/*   Updated: 2026/05/11 20:03:23 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <deque>
#include <iostream>
#include <list>
#include <vector>

#include "easyfind.hpp"

template <typename Container>
static void print_result(Container &container, int value)
{
	typename Container::iterator it = easyfind(container, value);

	std::cout << "Searching " << value << ": ";
	if (it == container.end())
		std::cout << "not found" << std::endl;
	else
		std::cout << "found at value " << *it << std::endl;
}

int main()
{
	std::vector<int> numbers;
	for (int i = 10; i <= 50; i += 10)
		numbers.push_back(i);

	std::list<int> values;
	values.push_back(1);
	values.push_back(3);
	values.push_back(5);
	values.push_back(7);

	std::deque<int> more_values;
	more_values.push_back(2);
	more_values.push_back(4);
	more_values.push_back(6);

	print_result(numbers, 30);
	print_result(numbers, 99);
	print_result(values, 5);
	print_result(values, 8);
	print_result(more_values, 4);
	print_result(more_values, 9);

	/*
	** Compile-time failure examples:
	** 1) A container with value_type, but not int, is rejected by is_same.
	** 2) A type without value_type is rejected by the SFINAE parameter.
	** easyfind() only accepts containers that expose value_type and are
	** containers of int.
	** If you uncomment the block below, the type has no value_type, so the
	** template argument substitution fails before easyfind() can be used.
	*/
	// In both cases, compilation would stop if these calls were enabled.
	// The first one fails because is_same<value_type, int>::value is false.
	// The second one fails earlier, because the default parameter tries to
	// use Container::value_type and the substitution is discarded.
#if 0
	std::vector<std::string> words;
	words.push_back("42");
	words.push_back("CPP");
	easyfind(words, 42);

	struct NoValueType {};
	NoValueType	no_value_type;
	easyfind(no_value_type, 42);

#endif
	return (0);
}
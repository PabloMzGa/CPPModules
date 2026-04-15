/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:15:00 by pablo            #+#    #+#             */
/*   Updated: 2026/04/15 18:15:00 by pablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		ScalarConverter::convert(argv[1]);
		return 0;
	}
	if (argc == 1)
	{
		const char *tests[] = {
			"a",
			"0",
			"7",
			"42",
			"-42",
			"42.0f",
			"42.5f",
			"42.0",
			"42.5",
			"nan",
			"nanf",
			"+inf",
			"-inf",
			"abc",
			"1.2.3",
			"+"
		};
		std::size_t i = 0;
		std::size_t count = sizeof(tests) / sizeof(tests[0]);

		while (i < count)
		{
			std::cout << "---- test: \"" << tests[i] << "\" ----" << std::endl;
			ScalarConverter::convert(tests[i]);
			std::cout << std::endl;
			++i;
		}
		return 0;
	}
	std::cerr << "Usage: " << argv[0] << " <literal>" << std::endl;
	std::cerr << "   or: " << argv[0] << " (run internal test suite)" << std::endl;
	return 1;
}

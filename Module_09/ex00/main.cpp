/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 18:10:00 by pablo             #+#    #+#             */
/*   Updated: 2026/06/18 21:05:32 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

/**
 * @brief Program entry point.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return `0` on success, `1` on invalid usage.
 */
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " input.txt" << std::endl;
		return 1;
	}

	try
	{
		BitcoinExchange exchange("data.csv");
		exchange.process_input(argv[1]);
	}
	catch (const std::exception &e)
	{
		return 1;
	}

	return 0;
}

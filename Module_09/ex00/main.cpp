/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 18:10:00 by pablo             #+#    #+#             */
/*   Updated: 2026/05/15 18:12:31 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	std::string data_path = "data.csv";
	std::string input_path = "test_input_ok.txt";

	if (argc == 3)
	{
		data_path = argv[1];
		input_path = argv[2];
	}
	else if (argc != 1)
	{
		std::cerr << "Usage: " << argv[0] << " [data.csv input.txt]" << std::endl;
		return 1;
	}

	std::cout << "Testing BitcoinExchange with:" << std::endl;
	std::cout << "  data  = " << data_path << std::endl;
	std::cout << "  input = " << input_path << std::endl;

	BitcoinExchange exchange(data_path, input_path);

	std::cout << "Construction finished" << std::endl;

	// Inspect maps from the object
	const std::map<std::string, float> &db = exchange.getData();

	std::cout << "Data entries: " << db.size() << std::endl;
	if (!db.empty())
	{
		std::cout << "First data entry: " << db.begin()->first << " => " << db.begin()->second << std::endl;
	}

	return 0;
}

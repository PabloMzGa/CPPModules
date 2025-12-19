/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:25:16 by pablo             #+#    #+#             */
/*   Updated: 2025/12/19 12:40:54 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

enum Level
{
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	INVALID
};

Level stringToLevel(const std::string &str)
{
	if (str == "DEBUG")
		return DEBUG;
	if (str == "INFO")
		return INFO;
	if (str == "WARNING")
		return WARNING;
	if (str == "ERROR")
		return ERROR;
	return INVALID;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Only one argument allowed!" << std::endl;
		return (1);
	}
	if (!argv[1][0])
	{
		std::cout << "Argument can't be empty!" << std::endl;
		return (1);
	}
	std::string input = argv[1];
	Level lvl = stringToLevel(input);
	Harl harl;

	switch (lvl)
	{
	case DEBUG:
		harl.complain("DEBUG");

	case INFO:
		harl.complain("INFO");

	case WARNING:
		harl.complain("WARNING");

	case ERROR:
		harl.complain("ERROR");
		break;
	default:
		std::cout << "Invalid level!" << std::endl;
		break;
	}
}

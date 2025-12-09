/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:08:24 by pablo             #+#    #+#             */
/*   Updated: 2025/12/09 19:05:17 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include "PhoneBook.hpp"
#include "colors.h"
#include <cstdio>
#include <iostream>
#include <string>

int	main(void)
{
	Contact		new_contact;
	PhoneBook	phonebook;
	char		loop;

	std::string input;
	loop = 1;
	while (loop)
	{
		std::cout << BOLD "Welcome to this Awesome Phonebook. Please enter the command "
							"(ADD, SEARCH, EXIT)" RESET
					<< std::endl;
		if (!std::getline(std::cin, input))
		{
			std::cout << MAGENTA "Bye!" RESET << std::endl;
			loop = 0;
		}
		else if (input == "ADD")
		{
			if (phonebook.add_command())
				std::cout << GREEN BOLD "Contact added" RESET << std::endl;
			else
			{
				if (std::cin.eof())
				{
					std::cin.clear();
					clearerr(stdin);
					std::cout << YELLOW "\nOperation cancelled" RESET << std::endl;
				}
			}
		}
		else if (input == "SEARCH")
		{
			if (!phonebook.search_command())
			{
				std::cin.clear();
				clearerr(stdin);
				std::cout << YELLOW "\nOperation cancelled" RESET << std::endl;
			}
		}
		else if (input == "EXIT")
		{
			std::cout << MAGENTA "Bye!" RESET << std::endl;
			loop = 0;
		}
		else
			std::cout << RED "Command not found, try again" RESET << std::endl;
	}
}

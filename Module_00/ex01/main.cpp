/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:08:24 by pablo             #+#    #+#             */
/*   Updated: 2025/11/23 14:00:15 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include "PhoneBook.hpp"
#include "colors.h"
#include <cstdio>
#include <iostream>
#include <string>


//TODO: Migrar printf a iomanip


int main()
{
	Contact new_contact;
	PhoneBook phonebook;
	std::string input;
	char loop = 1;

	while (loop)
	{

		std::cout << BOLD
		    "Welcome to this Awesome Phonebook. Please enter the command "
		    "(ADD, SEARCH, EXIT)" RESET
		          << std::endl;
		std::getline(std::cin, input);

		if (input == "ADD")
		{
			phonebook.add_command();
			std::cout << GREEN BOLD "Contact added" RESET << std::endl;
		}
		else if (input == "SEARCH")
			phonebook.search_command();
		else if (input == "EXIT")
		{
			std::cout << MAGENTA "Bye!" RESET << std::endl;
			loop = 0;
		}
		else
			std::cout << RED "Command not found, try again" RESET << std::endl;
	}
}

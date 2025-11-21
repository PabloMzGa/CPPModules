/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:08:24 by pablo             #+#    #+#             */
/*   Updated: 2025/11/21 17:16:07 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include "PhoneBook.hpp"
#include "colors.h"
#include <cstdio>
#include <iostream>
#include <string>


std::string truncate_string(std::string string)
{

}

void search_command(PhoneBook book)
{
	//TODO: Necesito truncar añadiendo un . en el caso de que sean más de 10 carácteres
	//por lo que tengo que hacer a mano el truncado
	printf("%10i|%.10s|%.10s|%.10s\n", book.contacts[0].id,
	       book.contacts[0].f_name.c_str(), book.contacts[0].l_name.c_str(),
	       book.contacts[0].nickname.c_str());
}

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
		{
			search_command(phonebook);
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

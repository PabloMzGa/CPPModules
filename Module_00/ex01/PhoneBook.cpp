/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:36:54 by pablo             #+#    #+#             */
/*   Updated: 2025/11/21 17:12:23 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <limits>
#include <string>
#include "colors.h"
#include <iostream>

/**
 * @brief Finds an available position in the phone book for adding a new
 * contact.
 *
 * This method iterates through the contacts array to find the first available
 * slot where a contact can be added. If no empty slots are found (all 8
 * positions are occupied), it returns the index of the oldest contact (the one
 * with the smallest ID) to be replaced.
 *
 * @return The index of the available position (0-7) in the contacts array.
 */
int PhoneBook::find_available_pos()
{
	int i = 0;
	int oldest_id = std::numeric_limits<int>::max();
	int oldest_index;

	while (i < 8)
	{
		if (this->contacts[i].id == -1)
			return i;
		else if (this->contacts[i].id < oldest_id)
		{
			oldest_id = this->contacts[i].id;
			oldest_index = i;
		}
		++i;
	}
	return (oldest_index);
}

/**
 * @brief Retrieves the highest ID among the contacts in the phone book.
 *
 * This function iterates through the first 8 contacts and finds the maximum ID value.
 * If no contacts have been added (all IDs are -1 or less), it returns -1.
 *
 * @return The highest ID found in the contacts array, or -1 if no valid IDs exist.
 */
int PhoneBook::get_newest_id()
{
	int i = 0;
	int newest_id = -1;

	while (i < 8)
	{
		if (this->contacts[i].id > newest_id)
			newest_id = this->contacts[i].id;
		++i;
	}
	return (newest_id);
}

void PhoneBook::add_contact(Contact *contact)
{
	int pos = find_available_pos();
	int id = get_newest_id();

	contact->id = id;
	this->contacts[pos] = *contact;

}

void PhoneBook::add_command()
{
	Contact contact;
	std::string input;

	std::cout << BOLD "First name" RESET << std::endl;
	std::getline(std::cin, input);
	contact.f_name = input;

	std::cout << BOLD "Last name" RESET << std::endl;
	std::getline(std::cin, input);
	contact.l_name = input;

	std::cout << BOLD "Nickname" RESET << std::endl;
	std::getline(std::cin, input);
	contact.nickname = input;

	std::cout << BOLD "Phone number" RESET << std::endl;
	std::getline(std::cin, input);
	contact.phone = input;

	std::cout << BOLD "Darkest secret" RESET << std::endl;
	std::getline(std::cin, input);
	contact.secret = input;

	this->add_contact(&contact);
}

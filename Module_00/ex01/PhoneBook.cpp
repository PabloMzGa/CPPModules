/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:36:54 by pablo             #+#    #+#             */
/*   Updated: 2025/11/23 13:59:54 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "colors.h"
#include <iostream>
#include <limits>
#include <string>

////////////////////// PRIVATE ////////////////////////////////

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
	unsigned int oldest_id = std::numeric_limits<unsigned int>::max();
	int oldest_index;

	while (i < 8)
	{
		if (this->contacts[i].id == 0)
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
 * This function iterates through the first 8 contacts and finds the maximum ID
 * value. If no contacts have been added (all IDs are 0), it returns 0.
 *
 * @return The highest ID found in the contacts array, or 0 if no valid IDs
 * exist.
 */
unsigned int PhoneBook::get_newest_id()
{
	int i = 0;
	unsigned int newest_id = 0;

	while (i < 8)
	{
		if (this->contacts[i].id > newest_id)
			newest_id = this->contacts[i].id;
		++i;
	}
	return (newest_id);
}

/**
 * @brief Adds a new contact to the phone book.
 *
 * This method finds an available position in the contacts array, assigns
 * a new unique ID to the contact,and stores the contact in that position.
 *
 * @param contact A pointer to the Contact object to be added.
 * The contact's ID will be set internally.
 */
void PhoneBook::add_contact(Contact *contact)
{
	int pos = find_available_pos();
	unsigned int id = get_newest_id();

	contact->id = id + 1;
	this->contacts[pos] = *contact;
}

/**
 * @brief Truncates a string to a maximum length of 10 characters, appending a
 * period if truncated.
 *
 * This function takes an input string and checks its length. If the string is
 * longer than 10 characters, it creates a copy, resizes it to 10 characters,
 * and replaces the last character with a period ('.'). If the string is 10
 * characters or shorter, it returns a copy of the original string unchanged.
 *
 * @param string The input string to be truncated.
 * @return A new std::string that is either the original string (if length <=
 * 10) or a truncated version ending with a period (if length > 10).
 */
std::string PhoneBook::truncate_string(std::string string)
{
	size_t len = string.size();
	std::string cpy = string;

	if (len > 10)
	{
		cpy.resize(10);
		cpy[9] = '.';
	}
	return (cpy);
}

Contact* PhoneBook::get_contact(unsigned int id)
{
	int i = 0;
	while (i < 8)
	{
		if (id == this->contacts[i].id)
			return (&this->contacts[i]);
		++i;
	}
	return (NULL);
}

////////////////////// PUBLIC ////////////////////////////////

/**
 * @brief Adds a new contact to the phone book by prompting the user for input.
 *
 * This method creates a new Contact object and prompts the user to enter
 * the first name, last name, nickname, phone number, and darkest secret.
 * Each input is read from standard input using std::getline and assigned
 * to the corresponding fields of the Contact. After collecting all inputs,
 * the contact is added to the phone book via the add_contact method.
 *
 * @note This function uses std::cin for input, which may leave a newline
 *       character in the input buffer from previous operations.
 *
 * @return void
 */
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

void PhoneBook::search_command()
{
	int i = 0;
	int id;
	char loop = 1;

	std::string input;
	while (i < 8 && this->contacts[i].id != 0)
	{
		printf("%10u|%10s|%10s|%10s\n", this->contacts[i].id,
		       truncate_string(this->contacts[i].f_name).c_str(),
		       truncate_string(this->contacts[i].l_name).c_str(),
		       truncate_string(this->contacts[i].nickname).c_str());
		++i;
	}
	while (loop)
	{

		std::cout << BOLD "Please, enter the contact's index, or write BACK to "
		                  "return to main menu" RESET
		          << std::endl;
		std::getline(std::cin, input);
		if (input == "BACK")
			return;
		try
		{
			id = static_cast<unsigned int>(std::stoul(input));
			Contact* found = get_contact(id);
			if (found)
			{
				std::cout << BOLD "First name: " RESET << found->f_name << std::endl;
				std::cout << BOLD "Last name: " RESET << found->l_name << std::endl;
				std::cout << BOLD "Nickname: " RESET << found->nickname << std::endl;
				std::cout << BOLD "Phone number: " RESET << found->phone << std::endl;
				std::cout << BOLD "Darkest secret: " RESET << found->secret << std::endl;
				loop = 0;
			}
			else
			{
				std::cout << BOLD YELLOW "Contact not found!" RESET << std::endl;
			}
		}
		catch (const std::invalid_argument &e)
		{
			std::cout << BOLD RED "Invalid id!" RESET << std::endl;
		}
	}
}

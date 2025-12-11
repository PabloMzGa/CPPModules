/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:36:54 by pablo             #+#    #+#             */
/*   Updated: 2025/12/11 20:14:48 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "colors.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

/////////////////////////////// PRIVATE ////////////////////////////////////////

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
	int				i;
	unsigned int	min_id;
	int				min_index_pos;

	i = 0;
	min_id = std::numeric_limits<unsigned int>::max();
	while (i < 8)
	{
		if (this->_contacts[i].get_id() == 0)
			return (i);
		else if (this->_contacts[i].get_id() < min_id)
		{
			min_id = this->_contacts[i].get_id();
			min_index_pos = i;
		}
		++i;
	}
	return (min_index_pos);
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
	int				i;
	unsigned int	newest_id;

	i = 0;
	newest_id = 0;
	while (i < 8)
	{
		if (this->_contacts[i].get_id() > newest_id)
			newest_id = this->_contacts[i].get_id();
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
	int				pos;
	unsigned int	id;

	pos = find_available_pos();
	id = get_newest_id();
	contact->set_id(id + 1);
	this->_contacts[pos] = *contact;
}

/**
 * @brief Truncates a string to a maximum length of 10 characters.
 *
 * If the input string is longer than 10 characters, it returns the first 9
 * characters followed by a period ('.'). Otherwise, it returns the string
 * unchanged.
 *
 * @param string The input string to be truncated.
 * @return std::string The truncated string or the original if it was 10
 * characters or less.
 */
std::string PhoneBook::truncate_string(std::string string)
{
	if (string.size() > 10)
		return (string.substr(0, 9) + ".");
	return (string);
}

/**
 * @brief Retrieves a contact from the phone book by its ID.
 *
 * This function iterates through the array of contacts (up to 8) and returns a
 * pointer to the contact whose ID matches the provided ID. If no matching
 * contact is found, it returns NULL.
 *
 * @param id The unique identifier of the contact to retrieve.
 * @return A pointer to the Contact object if found, or NULL if not found.
 */
Contact *PhoneBook::get_contact(unsigned int id)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (id == this->_contacts[i].get_id())
			return (&this->_contacts[i]);
		++i;
	}
	return (NULL);
}

/////////////////////////////// PUBLIC /////////////////////////////////////////

/**
 * @brief Prompts the user to input contact details and adds a new contact to
 * the phonebook.
 *
 * This function interactively collects information for a new contact, including
 * first name, last name, nickname, phone number, and darkest secret. It uses
 * std::getline to read input from std::cin. If input reading fails (e.g., due
 * to EOF), the function returns false. Otherwise, it creates a Contact object
 * with the provided details and adds it to the phonebook via add_contact().
 *
 * @return true if the contact was successfully added, false if input reading
 * failed.
 */
bool PhoneBook::add_command()
{
	Contact	contact;

	std::string input;
	std::cout << BOLD "First name" RESET << std::endl;
	while (true)
	{
		if (!std::getline(std::cin, input))
			return (false);
		if (contact.set_fname(input))
			break;
		std::cout << RED "First name cannot be empty. Please try again:" RESET << std::endl;
	}
	std::cout << BOLD "Last name" RESET << std::endl;
	while (true)
	{
		if (!std::getline(std::cin, input))
			return (false);
		if (contact.set_lname(input))
			break;
		std::cout << RED "Last name cannot be empty. Please try again:" RESET << std::endl;
	}
	std::cout << BOLD "Nickname" RESET << std::endl;
	while (true)
	{
		if (!std::getline(std::cin, input))
			return (false);
		if (contact.set_nickname(input))
			break;
		std::cout << RED "Nickname cannot be empty. Please try again:" RESET << std::endl;
	}
	std::cout << BOLD "Phone number" RESET << std::endl;
	while (true)
	{
		if (!std::getline(std::cin, input))
			return (false);
		if (contact.set_phone(input))
			break;
		std::cout << RED "Phone number cannot be empty. Please try again:" RESET << std::endl;
	}
	std::cout << BOLD "Darkest secret" RESET << std::endl;
	while (true)
	{
		if (!std::getline(std::cin, input))
			return (false);
		if (contact.set_secret(input))
			break;
		std::cout << RED "Darkest secret cannot be empty. Please try again:" RESET << std::endl;
	}
	this->add_contact(&contact);
	return (true);
}

/**
 * @brief Searches for and displays contact information in the phonebook.
 *
 * This method first checks if there are any contacts in the phonebook. If not,
 * it displays a message and returns true. Otherwise, it prints a formatted
 * table of up to 8 contacts showing their ID, truncated first name, last name,
 * and nickname. It then enters a loop prompting the user to enter a contact's
 * ID or "BACK" to return to the main menu. If a valid ID is entered and the
 * contact is found, it displays the full details of the contact (first name,
 * last name, nickname, phone number, and darkest secret). If the contact is not
 * found or the input is invalid, appropriate error messages are shown. The loop
 * continues until a valid contact is displayed or "BACK" is entered.
 *

	* @return (true if the search completes successfully or "BACK" is entered); false
 * if input reading fails.
 */
bool PhoneBook::search_command()
{
	int		i;
	int		id;
	char	loop;
	Contact	*found;

	if (!get_newest_id())
	{
		std::cout << RED "No contacts in phonebook yet!" RESET << std::endl;
		return (true);
	}
	i = 0;
	loop = 1;
	std::string input;
	std::cout << std::string(8,
		' ') << BOLD "Id" RESET "|" << BOLD "First Name" RESET "|"
				<< " " << BOLD "Last Name" RESET "|" << std::string(2,
					' ') << BOLD "Nickname" RESET << std::endl;
	while (i < 8 && this->_contacts[i].get_id() != 0)
	{
		std::cout << std::right << std::setw(10) << this->_contacts[i].get_id()
		<< "|" << std::right << std::setw(10) << truncate_string(this->_contacts[i].get_fname())
		<< "|" << std::right << std::setw(10) << truncate_string(this->_contacts[i].get_lname())
		<< "|" << std::right << std::setw(10) << truncate_string(this->_contacts[i].get_nickname())
		<< std::endl;
		++i;
	}
	while (loop)
	{
		std::cout << BOLD "Please, enter the contact's ID, or write BACK to "
							"return to main menu" RESET
					<< std::endl;
		if (!std::getline(std::cin, input))
			return (false);
		if (input == "BACK")
			return (true);
		id = atoi(input.c_str());
		if (id)
		{
			found = get_contact(id);
			if (found)
			{
				std::cout << BOLD "First name: " RESET << found->get_fname() << std::endl;
				std::cout << BOLD "Last name: " RESET << found->get_lname() << std::endl;
				std::cout << BOLD "Nickname: " RESET << found->get_nickname() << std::endl;
				std::cout << BOLD "Phone number: " RESET << found->get_phone() << std::endl;
				std::cout << BOLD "Darkest secret: " RESET << found->get_secret() << std::endl;
				return (true);
			}
			else
			{
				std::cout << BOLD YELLOW "Contact not found!" RESET << std::endl;
			}
		}
		else
		{
			std::cout << BOLD RED "Invalid id!" RESET << std::endl;
		}
	}
	return (true);
}

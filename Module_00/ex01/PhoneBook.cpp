/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:36:54 by pablo             #+#    #+#             */
/*   Updated: 2025/11/24 19:13:03 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "colors.h"
#include <iomanip>
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
	int				i;
	unsigned int	oldest_id;
	int				oldest_index;

	i = 0;
	oldest_id = std::numeric_limits<unsigned int>::max();
	while (i < 8)
	{
		if (this->contacts[i].id == 0)
			return (i);
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
	int				i;
	unsigned int	newest_id;

	i = 0;
	newest_id = 0;
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
	int				pos;
	unsigned int	id;

	pos = find_available_pos();
	id = get_newest_id();
	contact->id = id + 1;
	this->contacts[pos] = *contact;
}

std::string PhoneBook::truncate_string(std::string string)
{
	if (string.size() > 10)
		return (string.substr(0, 9) + ".");
	return (string);
}

Contact *PhoneBook::get_contact(unsigned int id)
{
	int	i;

	i = 0;
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
	Contact	contact;

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
	int		i;
	int		id;
	char	loop;
	Contact	*found;

	i = 0;
	loop = 1;
	std::string input;
	std::cout << std::string(8, ' ') << BOLD "Id" RESET "|"
	<< BOLD "First Name" RESET "|"
	<< " " << BOLD "Last Name" RESET "|"
	<< std::string(2, ' ') << BOLD "Nickname" RESET
	<< std::endl;
	while (i < 8 && this->contacts[i].id != 0)
	{
		std::cout << std::right << std::setw(10) << this->contacts[i].id << "|"
		<< std::right << std::setw(10) << truncate_string(this->contacts[i].f_name) << "|"
		<< std::right << std::setw(10) << truncate_string(this->contacts[i].l_name) << "|"
		<< std::right << std::setw(10) << truncate_string(this->contacts[i].nickname)  << std::endl;
		++i;
	}
	while (loop)
	{
		std::cout << BOLD "Please, enter the contact's index, or write BACK to "
							"return to main menu" RESET
					<< std::endl;
		std::getline(std::cin, input);
		if (input == "BACK")
			return ;
		try
		{
			id = static_cast<unsigned int>(std::stoul(input));
			found = get_contact(id);
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

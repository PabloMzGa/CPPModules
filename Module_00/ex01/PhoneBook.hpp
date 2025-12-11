/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:28:29 by pablo             #+#    #+#             */
/*   Updated: 2025/12/11 20:14:41 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
  private:
	int find_available_pos();
	unsigned int get_newest_id();
	void add_contact(Contact *contact);
	std::string truncate_string(std::string string);
	Contact* get_contact(unsigned int id);

	Contact _contacts[8];

  public:
	//Contact *get_contacts();
	bool add_command();
	bool search_command();
};

#endif

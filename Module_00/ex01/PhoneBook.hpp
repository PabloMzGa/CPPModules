/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:28:29 by pablo             #+#    #+#             */
/*   Updated: 2025/11/23 13:56:02 by pablo            ###   ########.fr       */
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

  public:
	Contact contacts[8];
	void add_command();
	void search_command();

};

#endif

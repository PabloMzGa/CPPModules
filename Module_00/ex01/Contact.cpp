/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:51:13 by pabmart2          #+#    #+#             */
/*   Updated: 2025/12/11 19:59:18 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

////////////////////////////////// CONSTRUCTOR /////////////////////////////////

Contact::Contact()
{
	_id = 0;
}

//////////////////////////////////// GETTERS ///////////////////////////////////

unsigned int Contact::get_id() { return _id; }

std::string Contact::get_fname() { return _f_name; }

std::string Contact::get_lname() { return _l_name; }

std::string Contact::get_nickname() { return _nickname; }

std::string Contact::get_phone() { return _phone; }

std::string Contact::get_secret() { return _secret; }

//////////////////////////////////// SETTERS ///////////////////////////////////

bool Contact::set_id(unsigned int id)
{
	_id = id;
	return true;
}

bool Contact::set_fname(std::string fname)
{
	if (fname.empty())
		return false;
	_f_name = fname;
	return true;
}

bool Contact::set_lname(std::string lname)
{
	if (lname.empty())
		return false;
	_l_name = lname;
	return true;
}

bool Contact::set_nickname(std::string nickname)
{
	if (nickname.empty())
		return false;
	_nickname = nickname;
	return true;
}

bool Contact::set_phone(std::string phone)
{
	if (phone.empty())
		return false;
	_phone = phone;
	return true;
}

bool Contact::set_secret(std::string secret)
{
	if (secret.empty())
		return false;
	_secret = secret;
	return true;
}

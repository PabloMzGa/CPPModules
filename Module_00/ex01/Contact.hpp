/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:37 by pablo             #+#    #+#             */
/*   Updated: 2025/12/11 20:10:36 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

class Contact
{
  public:

	Contact();

	unsigned int get_id();
	std::string get_fname();
	std::string get_lname();
	std::string get_nickname();
	std::string get_phone();
	std::string get_secret();

	bool set_id(unsigned int id);
	bool set_fname(std::string fname);
	bool set_lname(std::string lname);
	bool set_nickname(std::string nickname);
	bool set_phone(std::string phone);
	bool set_secret(std::string secret);

  private:
	unsigned int _id;
	std::string _f_name;
	std::string _l_name;
	std::string _nickname;
	std::string _phone;
	std::string _secret;
};

#endif

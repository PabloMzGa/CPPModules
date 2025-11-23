/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:37 by pablo             #+#    #+#             */
/*   Updated: 2025/11/23 13:19:37 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact
{
  public:
	Contact() : id(0) {}

	unsigned int id;
	std::string f_name;
	std::string l_name;
	std::string nickname;
	std::string phone;
	std::string secret;
};

#endif

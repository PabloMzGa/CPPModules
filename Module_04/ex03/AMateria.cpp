/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 19:34:05 by pablo             #+#    #+#             */
/*   Updated: 2025/12/25 14:32:32 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include <iostream>

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

AMateria::AMateria() : _type("unknown")
{
}

AMateria::AMateria(std::string const &type) : _type(type)
{
}

AMateria::AMateria(const AMateria &other) : _type(other._type)
{
}

AMateria &AMateria::operator=(const AMateria &other)
{
	(void)other;
	return *this;
}

AMateria::~AMateria()
{
}

/////////////////////////////// GETTERS & SETTERS //////////////////////////////

std::string const &AMateria::getType() const
{
	return _type;
}

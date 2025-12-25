/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:39:02 by pablo             #+#    #+#             */
/*   Updated: 2025/12/25 14:31:46 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
#include "ICharacter.hpp"
#include <iostream>

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

Ice::Ice() : AMateria("ice") {}

Ice::Ice(const Ice &copy) : AMateria(copy) {}

Ice &Ice::operator=(const Ice &src)
{
	(void)src;
	return *this;
}

Ice::~Ice() {}

AMateria* Ice::clone() const
{
	return new Ice(*this);
}

/////////////////////////////////// FUNCTIONS //////////////////////////////////

void Ice::use(ICharacter &target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}

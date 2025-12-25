/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:52:11 by pablo             #+#    #+#             */
/*   Updated: 2025/12/25 14:31:51 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"
#include "ICharacter.hpp"
#include <iostream>

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

Cure::Cure() : AMateria("cure") {}

Cure::Cure(const Cure &other) : AMateria(other) {}

Cure &Cure::operator=(const Cure &src)
{
	(void)src;
	return *this;
}

Cure::~Cure() {}

AMateria *Cure::clone() const
{
	return new Cure(*this);
}

/////////////////////////////////// FUNCTIONS //////////////////////////////////

void Cure::use(ICharacter &target) {

	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:37:55 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 21:39:53 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <iostream>

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

FragTrap::FragTrap() : ClapTrap()
{
	std::cout << "[FragTrap] Default constructor called" << std::endl;
	hp = 100;
	ep = 100;
	atk_dmg = 30;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	std::cout << "[FragTrap] Parameterized constructor called for FragTrap '" << name << "'" << std::endl;
	hp = 100;
	ep = 100;
	atk_dmg = 30;
}

FragTrap::FragTrap(const FragTrap &src) : ClapTrap(src)
{
	std::cout << "[FragTrap] Copy constructor called for FragTrap '" << name << "'" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &src)
{
	if (this != &src)
	{
		ClapTrap::operator=(src);
	}
	return *this;
}

FragTrap::~FragTrap()
{
	std::cout << "[FragTrap] Destructor called for FragTrap '" << name << "'" << std::endl;
}

/////////////////////////////////// FUNCTIONS //////////////////////////////////

void FragTrap::highFivesGuys(void)
{
	if (hp > 0 && ep > 0)
	{
		std::cout << "[FragTrap] highFivesGuys() called by '" << name << "'" << std::endl;
	}
	else
		std::cout << "[FragTrap] highFivesGuys() failed: insufficient HP or EP" << std::endl;
}

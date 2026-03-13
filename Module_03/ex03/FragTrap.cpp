/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:37:55 by pablo             #+#    #+#             */
/*   Updated: 2026/03/13 14:33:55 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <iostream>

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

FragTrap::FragTrap() : ClapTrap()
{
	hp = BASE_HP;
	ep = BASE_EP;
	atk_dmg = BASE_ATK;
	std::cout << "[FragTrap] Default constructor called" << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	hp = BASE_HP;
	ep = BASE_EP;
	atk_dmg = BASE_ATK;
	std::cout << "[FragTrap] Parameterized constructor called for FragTrap '" << name << "'" << std::endl;
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

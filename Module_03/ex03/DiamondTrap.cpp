/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:59:25 by pablo             #+#    #+#             */
/*   Updated: 2026/03/26 20:15:33 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include <iostream>

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

DiamondTrap::DiamondTrap() : ClapTrap("_clap_name"), FragTrap(), ScavTrap()
{
	this->name = "";
	hp = FragTrap::BASE_HP;
	ep = ScavTrap::BASE_EP;
	atk_dmg = FragTrap::BASE_ATK;
	std::cout << "[DiamondTrap] Default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name)
    : ClapTrap(name + "_clap_name"), FragTrap(name), ScavTrap(name), name(name)
{
	hp = FragTrap::BASE_HP;
	ep = ScavTrap::BASE_EP;
	atk_dmg = FragTrap::BASE_ATK;
	std::cout << "[DiamondTrap] Parameterized constructor called for DiamondTrap '" << this->name << "'" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &src)
    : ClapTrap(src), FragTrap(src), ScavTrap(src), name(src.name)
{
	std::cout << "[DiamondTrap] Copy constructor called for DiamondTrap '" << this->name << "'" << std::endl;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &src)
{
	if (this != &src)
	{
		this->name = src.name;
		ClapTrap::operator=(src);
	}
	return *this;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "[DiamondTrap] Destructor called for DiamondTrap '" << name
	          << "'" << std::endl;
}

/////////////////////////////////// FUNCTIONS //////////////////////////////////

void DiamondTrap::attack(const std::string &target)
{
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI()
{
	std::cout << "[DiamondTrap] Diamond name: " << DiamondTrap::name
	          << " | Claptrap name: " << ClapTrap::name << std::endl;
}

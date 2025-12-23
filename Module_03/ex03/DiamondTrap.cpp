/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:59:25 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 21:51:19 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include <iostream>

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

DiamondTrap::DiamondTrap() : FragTrap(), ScavTrap()
{
	std::cout << "[DiamondTrap] Default constructor called" << std::endl;
	DiamondTrap::name = "";
	ClapTrap::name = DiamondTrap::name + "_clap_name";
	this->hp = FragTrap::hp;
	this->ep = ScavTrap::ep;
	this->atk_dmg = FragTrap::atk_dmg;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name), FragTrap(name), ScavTrap(name)
{
	std::cout
	    << "[DiamondTrap] Parameterized constructor called for DiamondTrap '"
	    << name << "'" << std::endl;
	DiamondTrap::name = ClapTrap::name;
	ClapTrap::name = DiamondTrap::name + "_clap_name";
	this->hp = FragTrap::hp;
	this->ep = ScavTrap::ep;
	this->atk_dmg = FragTrap::atk_dmg;
}

DiamondTrap::DiamondTrap(const DiamondTrap &src) : ClapTrap(src), FragTrap(src), ScavTrap(src)
{
	std::cout << "[DiamondTrap] Copy constructor called for DiamondTrap '"
	          << name << "'" << std::endl;
	DiamondTrap::name = ClapTrap::name;
	ClapTrap::name = DiamondTrap::name + "_clap_name";
	this->hp = FragTrap::hp;
	this->ep = ScavTrap::ep;
	this->atk_dmg = FragTrap::atk_dmg;
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

void DiamondTrap::whoAmI()
{
	std::cout << "[DiamondTrap] Diamond name: " << DiamondTrap::name
	          << " | Claptrap name: " << ClapTrap::name << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:08:27 by pablo             #+#    #+#             */
/*   Updated: 2026/03/13 13:14:20 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include <iostream>

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

ScavTrap::ScavTrap() : ClapTrap()
{
	std::cout << "[ScavTrap] Default constructor called" << std::endl;
	hp = 100;
	ep = 50;
	atk_dmg = 20;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	std::cout << "[ScavTrap] Parameterized constructor called for ScavTrap '" << name << "'" << std::endl;
	hp = 100;
	ep = 50;
	atk_dmg = 20;
}

ScavTrap::ScavTrap(const ScavTrap &src) : ClapTrap(src)
{
	std::cout << "[ScavTrap] Copy constructor called for ScavTrap '" << name << "'" << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &src)
{
	if (this != &src)
	{
		ClapTrap::operator=(src);
	}
	return *this;
}

ScavTrap::~ScavTrap()
{
	std::cout << "[ScavTrap] Destructor called for ScavTrap '" << name << "'" << std::endl;
}

/////////////////////////////////// FUNCTIONS //////////////////////////////////

void ScavTrap::guardGate()
{
	std::cout << "[ScavTrap] guardGate() called by '" << name << "'" << std::endl;
}

void ScavTrap::attack(const std::string &target)
{
	if (hp > 0 && ep > 0)
	{
		--ep;
		std::cout << "[ScavTrap] attack() called by '" << name << "' on '" << target << "'" << std::endl;
	}
	else
		std::cout << "[ScavTrap] attack() failed: insufficient HP or EP" << std::endl;
}

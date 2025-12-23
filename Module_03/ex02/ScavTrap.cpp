/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:08:27 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 20:28:02 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include <iostream>

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

ScavTrap::ScavTrap() : ClapTrap()
{
	std::cout << "[ScavTrap] And I am even stronger! " << name
	          << ". Lets go to kill some skags!" << std::endl;
	hp = 100;
	ep = 50;
	atk_dmg = 20;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	std::cout << "[ScavTrap] And I am even stronger! " << name
	          << ". Lets go to kill some skags!" << std::endl;
	hp = 100;
	ep = 50;
	atk_dmg = 20;
}

ScavTrap::ScavTrap(const ScavTrap &src) : ClapTrap(src)
{
	std::cout << "[ScavTrap] And I am even stronger! " << name
	          << ". Lets go to kill some skags!" << std::endl;
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
	std::cout << "[ScavTrap] So much power for nothing..." << std::endl;
}

/////////////////////////////////// FUNCTIONS //////////////////////////////////

void ScavTrap::guardGate()
{
	std::cout << "Entering in Gatekeeper mode... You are not a real fan!"
	          << std::endl;
}

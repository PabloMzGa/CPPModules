/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:29:56 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 20:27:02 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

ClapTrap::ClapTrap() : name(""), hp(10), ep(10), atk_dmg(0)
{
	std::cout << "[ClapTrap] Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : name(name), hp(10), ep(10), atk_dmg(0)
{
	std::cout << "[ClapTrap] Parameterized constructor called for ClapTrap '" << name << "'" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &copy)
    : name(copy.name), hp(copy.hp), ep(copy.ep), atk_dmg(copy.atk_dmg)
{
	std::cout << "[ClapTrap] Copy constructor called for ClapTrap '" << name << "'" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &src)
{
	if (this != &src)
	{
		name = src.name;
		hp = src.hp;
		ep = src.ep;
		atk_dmg = src.atk_dmg;
	}
	return *this;
}

ClapTrap::~ClapTrap()
{
	std::cout << "[ClapTrap] Destructor called for ClapTrap '" << name << "'" << std::endl;
}

/////////////////////////////////// FUNCTIONS //////////////////////////////////

void ClapTrap::attack(const std::string &target)
{
	if (hp > 0 && ep > 0)
	{
		--ep;
		std::cout << "[ClapTrap] attack() called by '" << name << "' on '" << target << "'" << std::endl;
	}
	else
		std::cout << "[ClapTrap] attack() failed: insufficient HP or EP" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "[ClapTrap] takeDamage() called on '" << name << "', lost " << amount << " HP" << std::endl;
	if (hp > amount)
		hp -= amount;
	else if (hp != 0)
	{
		std::cout << "[ClapTrap] '" << name << "' died" << std::endl;
		hp = 0;
	}
	else
		std::cout << "[ClapTrap] takeDamage() failed: already dead" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (hp > 0 && ep > 0)
	{
		--ep;
		hp += amount;
		std::cout << "[ClapTrap] beRepaired() called on '" << name << "', gained " << amount << " HP" << std::endl;
	}
	else
		std::cout << "[ClapTrap] beRepaired() failed: insufficient HP or EP" << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:29:56 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 19:57:03 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

ClapTrap::ClapTrap() : name(""), hp(10), ep(10), atk_dmg(0)
{
	std::cout << "Hi my minion! I am " << name
	          << ". Lets go to kill some bandits!" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : name(name), hp(10), ep(10), atk_dmg(0)
{
	std::cout << "Hi my minion! I am " << name
	          << ". Lets go to kill some bandits!" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &copy)
    : name(copy.name), hp(copy.hp), ep(copy.ep), atk_dmg(copy.atk_dmg)
{
	std::cout << "Hi my minion! I am " << name
	          << ". Lets go to kill some bandits!" << std::endl;
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
	std::cout << "Damn you Handsome Jack! How did you know my worst enemy"
	             "are stairs?! Noooooooooooo"
	          << std::endl;
}

/////////////////////////////////// FUNCTIONS //////////////////////////////////

void ClapTrap::attack(const std::string &target)
{
	if (hp > 0 && ep > 0)
	{
		--ep;
		std::cout << name << " attacks " << target << " causing " << atk_dmg
		          << " points of damage!" << std::endl;
	}
	else
		std::cout << "Sad robot noises" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "Ouch! You shouldn't damage Hyperion's property! Now I have "
	             "lost "
	          << amount << " hit points" << std::endl;
	if (hp > amount)
		hp -= amount;
	else if (hp != 0)
	{
		std::cout << "Aaaaand... I die! " << std::endl;
		hp = 0;
	}
	else
		std::cout << "Sad robot noises" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (hp > 0 && ep > 0)
	{
		--ep;
		hp += amount;
		std::cout << "I have recovered " << amount
		          << " hit points. "
		             "This feels almost as good as opening doors..."
		          << std::endl;
	}
	else
		std::cout << "Sad robot noises" << std::endl;
}

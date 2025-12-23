/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:37:55 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 20:45:45 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <iostream>

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

FragTrap::FragTrap() : ClapTrap()
{
	std::cout << "[FragTrap] So much poweeeeeer! " << name
	          << ". Lets go to kill some loader bots!" << std::endl;
	hp = 100;
	ep = 100;
	atk_dmg = 30;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	std::cout << "[FragTrap] So much poweeeeeer! " << name
	          << ". Lets go to kill some loader bots!" << std::endl;
	hp = 100;
	ep = 100;
	atk_dmg = 30;
}

FragTrap::FragTrap(const FragTrap &src) : ClapTrap(src)
{
	std::cout << "[FragTrap] So much poweeeeeer! " << name
	          << ". Lets go to kill some loader bots!" << std::endl;
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
	std::cout << "[FragTrap] Even updated I was useless..." << std::endl;
}

/////////////////////////////////// FUNCTIONS //////////////////////////////////

void FragTrap::highFivesGuys(void)
{
	if (hp > 0 && ep > 0)
	{
		std::cout << "[FragTrap] High five my minion!" << std::endl;
	}
	else
		std::cout << "[FragTrap] Sad robot noises" << std::endl;
}

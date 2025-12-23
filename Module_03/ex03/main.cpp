/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:50:38 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 21:41:58 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Testing DiamondTrap Class ===" << std::endl;

	// Test default constructor
	DiamondTrap diamond1;
	diamond1.attack("Bandit");
	diamond1.whoAmI();

	// Test constructor with name
	DiamondTrap diamond2("Diamondy");
	diamond2.takeDamage(30);
	diamond2.beRepaired(20);
	diamond2.whoAmI();

	// Test copy constructor
	DiamondTrap diamond3(diamond2);
	diamond3.attack("Enemy");
	diamond3.whoAmI();

	// Test assignment operator
	diamond1 = diamond2;
	diamond1.attack("Another Enemy");
	diamond1.whoAmI();

	// Test DiamondTrap specific methods (inherited)
	diamond1.highFivesGuys();
	diamond1.guardGate();

	std::cout << "\n=== Test Complete ===" << std::endl;

	return 0;
}


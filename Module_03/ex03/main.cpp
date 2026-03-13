/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:50:38 by pablo             #+#    #+#             */
/*   Updated: 2026/03/13 14:33:56 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Testing DiamondTrap Class ===" << std::endl;

	// --- Default constructor ---
	std::cout << "\n--- Default constructor ---" << std::endl;
	DiamondTrap diamond1;
	diamond1.whoAmI();
	diamond1.attack("Bandit");
	diamond1.highFivesGuys();
	diamond1.guardGate();

	// --- Parameterized constructor ---
	std::cout << "\n--- Parameterized constructor ---" << std::endl;
	DiamondTrap diamond2("Diamondy");
	diamond2.whoAmI();
	diamond2.takeDamage(30);
	diamond2.beRepaired(20);
	diamond2.highFivesGuys();
	diamond2.guardGate();

	// --- Copy constructor ---
	std::cout << "\n--- Copy constructor ---" << std::endl;
	DiamondTrap diamond3(diamond2);
	diamond3.whoAmI();
	diamond3.attack("Enemy");

	// --- Assignment operator ---
	std::cout << "\n--- Assignment operator ---" << std::endl;
	diamond1 = diamond2;
	diamond1.whoAmI();
	diamond1.attack("Another Enemy");

	// --- Exhaust energy points ---
	std::cout << "\n--- Exhausting energy (ep = 50) ---" << std::endl;
	DiamondTrap diamond4("Depleted");
	for (unsigned int i = 0; i < 51; ++i)
		diamond4.attack("Target");

	// --- Take lethal damage ---
	std::cout << "\n--- Lethal damage ---" << std::endl;
	DiamondTrap diamond5("Mortally");
	diamond5.takeDamage(200);
	diamond5.attack("Ghost");
	diamond5.beRepaired(10);

	std::cout << "\n=== Test Complete ===" << std::endl;

	return 0;
}


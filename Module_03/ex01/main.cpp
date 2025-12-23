/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:50:38 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 20:31:47 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Testing ClapTrap Class ===" << std::endl;

	// Create a ClapTrap
	ClapTrap clap("Clappy");

	// Test assignment operator for ClapTrap
	ClapTrap clap_copy;
	clap_copy = clap;
	clap_copy.attack("Copy Bandit");
	clap.attack("Bandit");

	// Test taking damage
	clap.takeDamage(5);

	// Test repair
	clap.beRepaired(3);

	// Exhaust energy points with attacks
	for (int i = 0; i < 7; ++i)
	{
		clap.attack("Bandit");
	}

	// Try to attack without EP
	clap.attack("Captain Flynt");

	// Try to repair without EP
	clap.beRepaired(5);

	// Test taking more damage
	clap.takeDamage(10);

	// Try to attack without HP
	clap.attack("Ghost");

	// Try to repair without HP
	clap.beRepaired(5);

	std::cout << "\n=== Testing ScavTrap Class ===" << std::endl;

	// Test default constructor
	ScavTrap scav1;
	scav1.attack("Bandit");

	// Test constructor with name
	ScavTrap scav2("Scavy");
	scav2.takeDamage(20);
	scav2.beRepaired(10);

	// Test copy constructor
	ScavTrap scav3(scav2);
	scav3.attack("Enemy");

	// Test assignment operator
	scav1 = scav2;
	scav1.attack("Another Enemy");

	// Test ScavTrap specific method
	scav1.guardGate();

	std::cout << "\n=== Test Complete ===" << std::endl;

	return 0;
}


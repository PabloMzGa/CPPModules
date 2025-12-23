/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:50:38 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 19:57:48 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Testing ClapTrap Class ===" << std::endl;

	// Create a ClapTrap
	ClapTrap clap("Clappy");

	// Test attack
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

	std::cout << "=== Test Complete ===" << std::endl;

	return 0;
}


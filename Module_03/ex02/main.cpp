/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:50:38 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 20:49:21 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Testing FragTrap Class ===" << std::endl;

	// Test default constructor
	FragTrap frag1;
	frag1.attack("Bandit");

	// Test constructor with name
	FragTrap frag2("Fraggy");
	frag2.takeDamage(30);
	frag2.beRepaired(20);

	// Test copy constructor
	FragTrap frag3(frag2);
	frag3.attack("Enemy");

	// Test assignment operator
	frag1 = frag2;
	frag1.attack("Another Enemy");

	// Test FragTrap specific method
	frag1.highFivesGuys();

	std::cout << "\n=== Test Complete ===" << std::endl;

	return 0;
}


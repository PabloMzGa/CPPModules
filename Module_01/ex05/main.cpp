/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 20:33:04 by pabmart2          #+#    #+#             */
/*   Updated: 2025/12/18 20:23:32 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

int main() {
    Harl harl;

    std::cout << "=== Extensive tests of the Harl class ===" << std::endl;

    // Tests with valid levels
    std::cout << "\n--- Valid levels ---" << std::endl;
    std::cout << "Testing DEBUG:" << std::endl;
    harl.complain("DEBUG");

    std::cout << "\nTesting INFO:" << std::endl;
    harl.complain("INFO");

    std::cout << "\nTesting WARNING:" << std::endl;
    harl.complain("WARNING");

    std::cout << "\nTesting ERROR:" << std::endl;
    harl.complain("ERROR");

    // Tests with invalid levels
    std::cout << "\n--- Invalid levels ---" << std::endl;
    std::cout << "Testing 'debug' (lowercase):" << std::endl;
    harl.complain("debug");  // Should do nothing

    std::cout << "\nTesting empty string:" << std::endl;
    harl.complain("");

    std::cout << "\nTesting 'WARNING' again:" << std::endl;
    harl.complain("WARNING");

    // Multiple calls tests
    std::cout << "\n--- Multiple calls ---" << std::endl;
    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR", "UNKNOWN"};
    for (int i = 0; i < 5; ++i) {
        std::cout << "Call " << (i + 1) << " with '" << levels[i] << "':" << std::endl;
        harl.complain(levels[i]);
        std::cout << std::endl;
    }

    std::cout << "=== End of tests ===" << std::endl;
    return 0;
}


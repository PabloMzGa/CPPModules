/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 23:54:47 by pablo             #+#    #+#             */
/*   Updated: 2026/03/13 12:57:34 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

int main(void)
{
	std::cout << "=== Testing Fixed Class Operators ===\n" << std::endl;

	// Create some Fixed objects
	Fixed a(10.5f);
	Fixed b(5.25f);
	Fixed c(10.5f);
	Fixed d;

	std::cout << "Initial values:" << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << std::endl;

	// Arithmetic operators
	std::cout << "=== Arithmetic Operators ===" << std::endl;
	std::cout << "a + b = " << (a + b) << std::endl;
	std::cout << "a - b = " << (a - b) << std::endl;
	std::cout << "a * b = " << (a * b) << std::endl;
	std::cout << "a / b = " << (a / b) << std::endl;
	std::cout << std::endl;

	// Comparison operators
	std::cout << "=== Comparison Operators ===" << std::endl;
	std::cout << "a == c: " << (a == c) << std::endl;
	std::cout << "a != b: " << (a != b) << std::endl;
	std::cout << "a < b: " << (a < b) << std::endl;
	std::cout << "a > b: " << (a > b) << std::endl;
	std::cout << "a <= c: " << (a <= c) << std::endl;
	std::cout << "a >= b: " << (a >= b) << std::endl;
	std::cout << std::endl;

	// Increment/Decrement operators
	std::cout << "=== Increment/Decrement Operators ===" << std::endl;
	Fixed e = a; // Copy for testing
	std::cout << "e (copy of a) = " << e << std::endl;
	std::cout << "++e = " << ++e << std::endl;
	std::cout << "e after ++e = " << e << std::endl;
	std::cout << "e++ = " << e++ << std::endl;
	std::cout << "e after e++ = " << e << std::endl;
	std::cout << "--e = " << --e << std::endl;
	std::cout << "e after --e = " << e << std::endl;
	std::cout << "e-- = " << e-- << std::endl;
	std::cout << "e after e-- = " << e << std::endl;
	std::cout << std::endl;

	// Min/Max functions
	std::cout << "=== Min/Max Functions ===" << std::endl;
	Fixed f(7.5f);
	Fixed g(12.3f);
	std::cout << "f = " << f << ", g = " << g << std::endl;
	std::cout << "max(f, g) = " << Fixed::max(f, g) << std::endl;
	std::cout << "min(f, g) = " << Fixed::min(f, g) << std::endl;

	// Test with const objects
	const Fixed const_f(8.0f);
	const Fixed const_g(15.0f);
	std::cout << "const_f = " << const_f << ", const_g = " << const_g << std::endl;
	std::cout << "max(const_f, const_g) = " << Fixed::max(const_f, const_g) << std::endl;
	std::cout << "min(const_f, const_g) = " << Fixed::min(const_f, const_g) << std::endl;
	std::cout << std::endl;

	// Test assignment and copy
	std::cout << "=== Assignment and Copy ===" << std::endl;
	Fixed h;
	h = a;
	std::cout << "h after h = a: " << h << std::endl;
	Fixed i(a);
	std::cout << "i (copy constructed from a): " << i << std::endl;
	std::cout << std::endl;

	// Test with negative numbers
	std::cout << "=== Negative Numbers Tests ===" << std::endl;
	Fixed neg_a(-10.5f);
	Fixed neg_b(5.25f);
	Fixed neg_c(-5.25f);
	std::cout << "neg_a = " << neg_a << ", neg_b = " << neg_b << ", neg_c = " << neg_c << std::endl;
	std::cout << "neg_a * neg_b = " << (neg_a * neg_b) << std::endl;
	std::cout << "neg_a * neg_c = " << (neg_a * neg_c) << std::endl;
	std::cout << "neg_a / neg_b = " << (neg_a / neg_b) << std::endl;
	std::cout << "neg_b / neg_a = " << (neg_b / neg_a) << std::endl;
	std::cout << "neg_a + neg_c = " << (neg_a + neg_c) << std::endl;
	std::cout << "neg_a - neg_c = " << (neg_a - neg_c) << std::endl;

	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:08:00 by pablo             #+#    #+#             */
/*   Updated: 2026/04/15 19:00:22 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

int main(void)
{
	Data original;
	original.setValue(42);

	uintptr_t raw = Serializer::serialize(&original);
	Data *restored = Serializer::deserialize(raw);

	std::cout << "=== Serializer test ===" << std::endl;
	std::cout << "original ptr: " << &original << std::endl;
	std::cout << "raw value   : " << raw << std::endl;
	std::cout << "restored ptr: " << restored << std::endl;
	std::cout << "same address: " << (&original == restored) << std::endl;
	std::cout << "value       : " << restored->getValue() << std::endl;

	Data copy(original);
	Data assigned;
	assigned = original;

	original.setValue(7);

	std::cout << std::endl;
	std::cout << "=== Data canonical form test ===" << std::endl;
	std::cout << "original value: " << original.getValue() << std::endl;
	std::cout << "copy value    : " << copy.getValue() << std::endl;
	std::cout << "assigned value: " << assigned.getValue() << std::endl;

	uintptr_t rawNull = Serializer::serialize(0);
	Data *nullData = Serializer::deserialize(rawNull);

	std::cout << std::endl;
	std::cout << "=== Null pointer test ===" << std::endl;
	std::cout << "null raw      : " << rawNull << std::endl;
	std::cout << "null restored : " << nullData << std::endl;

	return (0);
}

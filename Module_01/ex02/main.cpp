/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:10:15 by pablo             #+#    #+#             */
/*   Updated: 2025/12/13 12:18:38 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int main ()
{
	std::string string = "HI THIS IS BRAIN";
	std::string *string_PTR = &string;
	std::string &string_REF = string;

	std::cout << "string memory address: " << static_cast<void*>(&string) << std::endl;
	std::cout << "string_PTR memory address helded: " << static_cast<void*>(string_PTR) << std::endl;
	std::cout << "string_REF memory address helded: " << static_cast<void*>(&string_REF) << std::endl;

	std::cout << "string value: " << string << std::endl;
	std::cout << "string_PTR pointed value: " << *string_PTR << std::endl;
	std::cout << "string_REF pinted value: " << string_REF << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 20:14:04 by pablo             #+#    #+#             */
/*   Updated: 2026/05/19 20:24:58 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RNP.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	RNP rnp;

	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " \"Expresion in RNP\""
				  << std::endl;
		return 1;
	}
	try
	{
		std::cout << rnp.calculate(std::string(argv[1])) << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

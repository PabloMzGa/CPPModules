/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:41:09 by pablo             #+#    #+#             */
/*   Updated: 2026/03/18 17:58:25 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <iostream>

int main()
{
	try
	{
		Bureaucrat a("Alice", 2);
		std::cout << a;
		a.promote(1);
		std::cout << "Promoted: " << a;
		a.promote(1); // should throw
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	try
	{
		Bureaucrat b("Bob", 150);
		std::cout << b;
		b.demote(1); // should throw
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	try
	{
		Bureaucrat c("TooHigh", 0);
	}
	catch (std::exception &e)
	{
		std::cout << "Construction exception: " << e.what() << std::endl;
	}

	try
	{
		Bureaucrat d("TooLow", 151);
	}
	catch (std::exception &e)
	{
		std::cout << "Construction exception: " << e.what() << std::endl;
	}

	return 0;
}

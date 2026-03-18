/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:41:09 by pablo             #+#    #+#             */
/*   Updated: 2026/03/18 19:01:58 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
	// Bureaucrat tests (existing)
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

	// Form tests
	std::cout << "\n--- Form tests ---\n";
	try
	{
		Form f1("FormA", 2, 3);
		std::cout << "Created Form: " << f1 << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Form construction exception: " << e.what() << std::endl;
	}

	try
	{
		Form f2("TooHighForm", 0, 10); // should throw
	}
	catch (std::exception &e)
	{
		std::cout << "Form construction exception: " << e.what() << std::endl;
	}

	try
	{
		Form f3("TooLowForm", 10, 151); // should throw
	}
	catch (std::exception &e)
	{
		std::cout << "Form construction exception: " << e.what() << std::endl;
	}

	// Default constructors
	std::cout << "\n--- Default constructors ---\n";
	Bureaucrat defB;
	Form defF;
	std::cout << defB;
	std::cout << "Default Form: " << defF << std::endl;

	// Getters test for Form
	std::cout << "\n--- Form getters ---\n";
	try
	{
		Form gf("GForm", 42, 100);
		std::cout << "getName(): " << gf.getName() << std::endl;
		std::cout << std::boolalpha << "getSigned(): " << gf.getSigned() << std::noboolalpha << std::endl;
		std::cout << "getSignGrade(): " << gf.getSignGrade() << std::endl;
		std::cout << "getExecGrade(): " << gf.getExecGrade() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Form construction exception: " << e.what() << std::endl;
	}

	// Signing process
	std::cout << "\n--- Signing process ---\n";
	try
	{
		Form sform("SignTest", 45, 100);
		Bureaucrat low("Low", 50);
		std::cout << low;
		std::cout << sform;
		low.signForm(sform); // should fail
		Bureaucrat high("High", 40);
		std::cout << high;
		high.signForm(sform); // should succeed
		std::cout << sform;
	}
	catch (std::exception &e)
	{
		std::cout << "Signing exception: " << e.what() << std::endl;
	}

	return 0;
}

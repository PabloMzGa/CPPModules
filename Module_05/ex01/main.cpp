/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:41:09 by pablo             #+#    #+#             */
/*   Updated: 2026/04/17 19:33:39 by pablo            ###   ########.fr       */
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

	// Test 1: Bureaucrat with insufficient grade
	try
	{
		Form sform("SignTest", 45, 100);
		Bureaucrat low("Low", 50);
		std::cout << "Bureaucrat: " << low;
		std::cout << sform;
		std::cout << "Attempting to sign with insufficient grade...\n";
		low.signForm(sform);
		std::cout << "Form after attempt: " << sform;
	}
	catch (std::exception &e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// Test 2: Bureaucrat with sufficient grade
	std::cout << "\n--- Test 2: Sufficient grade ---\n";
	try
	{
		Form sform2("SignTest2", 45, 100);
		Bureaucrat high("High", 40);
		std::cout << "Bureaucrat: " << high;
		std::cout << sform2;
		std::cout << "Attempting to sign with sufficient grade...\n";
		high.signForm(sform2);
		std::cout << "Form after signing: " << sform2;
	}
	catch (std::exception &e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// Test 3: Try to sign already signed form
	std::cout << "\n--- Test 3: Already signed form ---\n";
	try
	{
		Form sform3("SignTest3", 45, 100);
		Bureaucrat high("High", 40);
		high.signForm(sform3);
		std::cout << "Form is now signed. Trying to sign again...\n";
		high.signForm(sform3);
	}
	catch (std::exception &e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	return 0;
}

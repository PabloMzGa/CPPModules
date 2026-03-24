#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <iostream>
#include <string>

static void section(const std::string &name)
{
	std::cout << "\n========== " << name << " ==========" << std::endl;
}

static void createdBureaucrat(const Bureaucrat &b)
{
	std::cout << "[CREATE] Bureaucrat: " << b.getName() << " (grade "
		<< b.getGrade() << ")" << std::endl;
}

static void action(const std::string &message)
{
	std::cout << "[ACTION] " << message << std::endl;
}

static void actionAttempt(const std::string &message, int attempt)
{
	std::cout << "[ACTION] " << message << " (attempt " << attempt
		<< ")" << std::endl;
}

static void testShrubbery()
{
	section("ShrubberyCreationForm");

	Bureaucrat low("Low", 150);
	Bureaucrat signer("Gardener", 140);
	Bureaucrat executor("Executor", 130);
	ShrubberyCreationForm form("home");
	createdBureaucrat(low);
	createdBureaucrat(signer);
	createdBureaucrat(executor);
	std::cout << "[CREATE] Form: " << form.getName() << " (target "
		<< form.getTarget() << ")" << std::endl;

	std::cout << form;
	action("Low tries to sign ShrubberyCreationForm");
	low.signForm(form);
	action("Gardener signs ShrubberyCreationForm");
	signer.signForm(form);

	try
	{
		action("Low tries to execute ShrubberyCreationForm");
		form.execute(low);
	}
	catch (const std::exception &e)
	{
		std::cout << "Execution with low grade failed as expected: " << e.what()
			<< std::endl;
	}

	try
	{
		action("Executor executes ShrubberyCreationForm");
		form.execute(executor);
		std::cout << "Shrubbery file should be created: home_shrubbery"
			<< std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Unexpected shrubbery execution failure: " << e.what()
			<< std::endl;
	}
}

static void testRobotomy()
{
	section("RobotomyRequestForm");

	Bureaucrat signer("Technician", 70);
	Bureaucrat executor("Driller", 40);
	RobotomyRequestForm unsignedForm("Marvin");
	RobotomyRequestForm signedForm("Bender");
	createdBureaucrat(signer);
	createdBureaucrat(executor);
	std::cout << "[CREATE] Form: " << unsignedForm.getName() << " (target "
		<< unsignedForm.getTarget() << ")" << std::endl;
	std::cout << "[CREATE] Form: " << signedForm.getName() << " (target "
		<< signedForm.getTarget() << ")" << std::endl;

	try
	{
		action("Driller tries to execute unsigned RobotomyRequestForm");
		unsignedForm.execute(executor);
	}
	catch (const std::exception &e)
	{
		std::cout << "Unsigned form execution failed as expected: " << e.what()
			<< std::endl;
	}

	action("Technician signs RobotomyRequestForm (Bender)");
	signer.signForm(signedForm);
	for (int i = 0; i < 4; ++i)
	{
		try
		{
			actionAttempt("Driller executes RobotomyRequestForm", i + 1);
			signedForm.execute(executor);
		}
		catch (const std::exception &e)
		{
			std::cout << "Unexpected robotomy execution failure: " << e.what()
				<< std::endl;
		}
	}
}

static void testPresidential()
{
	section("PresidentialPardonForm");

	Bureaucrat low("Intern", 50);
	Bureaucrat signer("Minister", 25);
	Bureaucrat executor("President", 1);
	PresidentialPardonForm form("Arthur Dent");
	createdBureaucrat(low);
	createdBureaucrat(signer);
	createdBureaucrat(executor);
	std::cout << "[CREATE] Form: " << form.getName() << " (target "
		<< form.getTarget() << ")" << std::endl;

	action("Intern tries to sign PresidentialPardonForm");
	low.signForm(form);
	action("Minister signs PresidentialPardonForm");
	signer.signForm(form);

	try
	{
		action("Intern tries to execute PresidentialPardonForm");
		form.execute(low);
	}
	catch (const std::exception &e)
	{
		std::cout << "Execution with low grade failed as expected: " << e.what()
			<< std::endl;
	}

	try
	{
		action("President executes PresidentialPardonForm");
		form.execute(executor);
	}
	catch (const std::exception &e)
	{
		std::cout << "Unexpected pardon execution failure: " << e.what()
			<< std::endl;
	}
}

int main()
{
	try
	{
		testShrubbery();
		testRobotomy();
		testPresidential();
	}
	catch (const std::exception &e)
	{
		std::cout << "Fatal error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}

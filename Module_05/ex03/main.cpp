#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"

#include <iostream>
#include <string>

static void section(const std::string &name)
{
	std::cout << "\n========== " << name << " ==========" << std::endl;
}

static void testValidForm(Intern &intern, const std::string &formName,
	const std::string &target, Bureaucrat &boss)
{
	AForm *form = NULL;

	section("Testing: " + formName + " -> " + target);
	try
	{
		form = intern.makeForm(formName, target);
		std::cout << *form;
		boss.signForm(*form);
		form->execute(boss);
		std::cout << "Execution done" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Unexpected error: " << e.what() << std::endl;
	}
	delete form;
}

static void testInvalidForm(Intern &intern, const std::string &formName)
{
	section("Testing invalid form: " + formName);
	try
	{
		AForm *form = intern.makeForm(formName, "nobody");
		delete form;
		std::cout << "Error: invalid form was created" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Expected error: " << e.what() << std::endl;
	}
}

int main()
{
	Intern someRandomIntern;
	Bureaucrat boss("Boss", 1);

	testValidForm(someRandomIntern, "shrubbery creation", "home", boss);
	testValidForm(someRandomIntern, "robotomy request", "Bender", boss);
	testValidForm(someRandomIntern, "presidential pardon", "Arthur Dent", boss);
	testValidForm(someRandomIntern, "  RoBoToMy   ReQuEsT ", "Marvin", boss);
	testInvalidForm(someRandomIntern, "coffee request");

	return (0);
}

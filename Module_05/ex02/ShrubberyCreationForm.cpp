/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:50:10 by pablo             #+#    #+#             */
/*   Updated: 2026/03/24 19:25:36 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "AForm.hpp"
#include <fstream>
#include <iostream>

////////////////////////////////// CANONICAL ///////////////////////////////////

ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("ShrubberyCreationForm", SHRUBBERY_SIGN_GRADE,
		SHRUBBERY_EXEC_GRADE, "default")
{
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
	: AForm("ShrubberyCreationForm", SHRUBBERY_SIGN_GRADE,
		SHRUBBERY_EXEC_GRADE, target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm &copy)
    : AForm(copy)
{
}

ShrubberyCreationForm &
ShrubberyCreationForm::operator=(const ShrubberyCreationForm &src)
{
	if (this != &src)
	{
		AForm::operator=(src);
	}
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::execute(Bureaucrat const &executor)
{
	std::string filename;

	filename = getTarget() + "_shrubbery";
	try
	{
		AForm::execute(executor);
		std::ofstream ofs;
		ofs.exceptions(std::ofstream::failbit | std::ofstream::badbit);
		ofs.open(filename.c_str());
		const char *tree =
			"        /\\\n"
			"       /  \\\n"
			"      /++++\\\n"
			"     /  ()  \\\n"
			"    /        \\\n"
			"   /~`~`~`~`~`\\\n"
			"  / ()  ()  () \\\n"
			" /______________\\\n"
			"        ||\n"
			"        ||\n";
		ofs << tree;
		ofs.close();
	}
	catch (const std::ios_base::failure &e)
	{
		std::cerr << "Error creating shrubbery file '" << filename << "': "
			<< e.what() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error executing form '" << getName() << "': "
			<< e.what() << std::endl;
		throw;
	}
}

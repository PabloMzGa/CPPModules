/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:50:10 by pablo             #+#    #+#             */
/*   Updated: 2026/04/17 19:43:23 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"
#include "AForm.hpp"
#include <iostream>

////////////////////////////////// CANONICAL ///////////////////////////////////

PresidentialPardonForm::PresidentialPardonForm()
	: AForm("PresidentialPardonForm", PRESIDENTIAL_SIGN_GRADE,
		PRESIDENTIAL_EXEC_GRADE, "default")
{
}

PresidentialPardonForm::PresidentialPardonForm(std::string target)
	: AForm("PresidentialPardonForm", PRESIDENTIAL_SIGN_GRADE,
		PRESIDENTIAL_EXEC_GRADE, target)
{
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm &copy)
    : AForm(copy)
{
}

PresidentialPardonForm &
PresidentialPardonForm::operator=(const PresidentialPardonForm &src)
{
	if (this != &src)
	{
		AForm::operator=(src);
	}
	return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm() {}


void PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	try
	{
		AForm::execute(executor);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error executing form '" << getName() << "': " << e.what()
		          << std::endl;
		throw;
	}
	std::cout << getTarget() << " has been pardoned by the President"
				<< " Zaphod Beeblebrox" << std::endl;

}

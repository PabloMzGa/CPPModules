/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:50:10 by pablo             #+#    #+#             */
/*   Updated: 2026/04/23 18:54:51 by pabmart2         ###   ########.fr       */
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

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &copy)
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
	AForm::execute(executor);
	std::cout << getTarget() << " has been pardoned by the President"
				<< " Zaphod Beeblebrox" << std::endl;

}

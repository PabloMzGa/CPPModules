/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:50:10 by pablo             #+#    #+#             */
/*   Updated: 2026/04/23 18:54:52 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include "AForm.hpp"
#include <ctime>
#include <iostream>
#include <stdlib.h> // for random(), srandom()

////////////////////////////////// CANONICAL ///////////////////////////////////

RobotomyRequestForm::RobotomyRequestForm()
	: AForm("RobotomyRequestForm", ROBOTOMY_SIGN_GRADE,
		ROBOTOMY_EXEC_GRADE, "default")
{
}

RobotomyRequestForm::RobotomyRequestForm(std::string target)
	: AForm("RobotomyRequestForm", ROBOTOMY_SIGN_GRADE,
		ROBOTOMY_EXEC_GRADE, target)
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &copy)
    : AForm(copy)
{
}

RobotomyRequestForm &
RobotomyRequestForm::operator=(const RobotomyRequestForm &src)
{
	if (this != &src)
	{
		AForm::operator=(src);
	}
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm() {}

// POSIX helper: 50/50 choice using random()
static inline bool random50()
{
	return (random() & 1) == 0;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	AForm::execute(executor);

	static bool seeded = false;
	if (!seeded)
	{
		srandom(static_cast<unsigned int>(std::time(NULL)));
		seeded = true;
	}

	std::cout << "Bzzzzzz... drilling noises...\n";

	bool success = random50();
	if (success)
		std::cout << getTarget() << " has been robotomized successfully"
		          << std::endl;
	else
		std::cout << "The robotomy failed on " << getTarget() << std::endl;
}

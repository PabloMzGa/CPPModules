/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auto-generated                             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24  by assistant                        #+#    #+# */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cctype>
#include <iostream>

////////////////////////////////// CANONICAL ///////////////////////////////////

Intern::Intern() {}

Intern::Intern(const Intern &copy)
{
	(void)copy;
}

Intern &Intern::operator=(const Intern &src)
{
	(void)src;
	return *this;
}

Intern::~Intern() {}

////////////////////////////////// EXCEPTIONS //////////////////////////////////

Intern::FormNameNotFoundException::FormNameNotFoundException(const std::string &name)
{
	msg = std::string("Error: Form ") + name + " not found";
}

Intern::FormNameNotFoundException::~FormNameNotFoundException() throw() {}

const char *Intern::FormNameNotFoundException::what() const throw()
{
	return msg.c_str();
}

/////////////////////////////////// MEMBER /////////////////////////////////////


struct FormEntry
{
	const char *name;
	const char *normalizedName;
	AForm *(*creator)(const std::string &);
};

static AForm *createShrubbery(const std::string &target)
{
	return new ShrubberyCreationForm(target);
}

static AForm *createRobotomy(const std::string &target)
{
	return new RobotomyRequestForm(target);
}

static AForm *createPresidential(const std::string &target)
{
	return new PresidentialPardonForm(target);
}

static const FormEntry formTable[] = {
	{"shrubbery creation", "shrubberycreation", &createShrubbery},
	{"robotomy request", "robotomyrequest", &createRobotomy},
	{"presidential pardon", "presidentialpardon", &createPresidential}
};
static const int formTableSize = sizeof(formTable) / sizeof(FormEntry);

static std::string normalizeFormName(const std::string &name)
{
	std::string normalized;
	normalized.reserve(name.size());
	for (std::string::size_type i = 0; i < name.size(); ++i)
	{
		unsigned char c = static_cast<unsigned char>(name[i]);
		if (!std::isspace(c))
			normalized += static_cast<char>(std::tolower(c));
	}
	return normalized;
}

AForm *Intern::makeForm(const std::string &formName, const std::string &target) const
{
	const std::string normalizedInput = normalizeFormName(formName);

	for (int i = 0; i < formTableSize; ++i)
	{
		if (normalizedInput == formTable[i].normalizedName)
		{
			std::cout << "Intern creates " << formTable[i].name << std::endl;
			return formTable[i].creator(target);
		}
	}
	throw Intern::FormNameNotFoundException(formName);
}

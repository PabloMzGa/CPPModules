/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:21:10 by pablo             #+#    #+#             */
/*   Updated: 2026/03/18 18:00:20 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <ostream>

////////////////////////////////// CANONICAL ///////////////////////////////////

Bureaucrat::Bureaucrat(std::string name, int grade)
{
	if (grade < MAX_GRADE)
		throw GradeTooHighException();
	else if (grade > MIN_GRADE)
		throw GradeTooLowException();
	_name = name;
	_grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat &copy)
{
	*this = copy;
}

Bureaucrat::~Bureaucrat() {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &src)
{
	if (this != &src)
	{
		this->_name = src._name;
		this->_grade = src._grade;
	}
	return (*this);
}

////////////////////////////////// OPERATORS ///////////////////////////////////
std::ostream &operator<<(std::ostream &os, const Bureaucrat &b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
	return (os);
}

////////////////////////////////// EXCEPTIONS //////////////////////////////////

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Error: Grade too high");
}
const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Error: Grade too low");
}

/////////////////////////////////// GETTERS ////////////////////////////////////

std::string Bureaucrat::getName() const
{
	return (_name);
}

int Bureaucrat::getGrade() const
{
	return (_grade);
}

/////////////////////////////////// MEMBERS ////////////////////////////////////

void Bureaucrat::promote(unsigned int steps)
{
	if (steps - _grade < MAX_GRADE)
		throw GradeTooHighException();
	_grade -= steps;
}

void Bureaucrat::demote(unsigned int steps)
{
	if (steps + _grade > MIN_GRADE)
		throw GradeTooHighException();
	_grade += steps;
}

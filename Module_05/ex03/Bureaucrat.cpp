/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:21:10 by pablo             #+#    #+#             */
/*   Updated: 2026/04/22 20:58:50 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include <iostream>
#include <ostream>

////////////////////////////////// CANONICAL ///////////////////////////////////

Bureaucrat::Bureaucrat() : _name("default"), _grade(MIN_GRADE) {}

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name)
{
	if (grade < MAX_GRADE)
		throw GradeTooHighException();
	else if (grade > MIN_GRADE)
		throw GradeTooLowException();
	_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &copy)
    : _name(copy._name), _grade(copy._grade)
{
}

Bureaucrat::~Bureaucrat() {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &src)
{
	if (this != &src)
	{
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
	if (steps >= static_cast<unsigned int>(_grade))
		throw GradeTooHighException();
	_grade -= steps;
}

void Bureaucrat::demote(unsigned int steps)
{
	if (steps + _grade > MIN_GRADE)
		throw GradeTooLowException();
	_grade += steps;
}

void Bureaucrat::signForm(AForm &f)
{
	if (f.getSigned())
	{
		std::cout << _name << " couldn't sign form " << f.getName()
		          << ". Is already signed!" << std::endl;
		return;
	}
	try
	{
		f.beSigned(*this);
		std::cout << _name << " signed form " << f.getName() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << _name << " couldn't sign form " << f.getName() << ". "
		          << e.what() << std::endl;
	}
}
void Bureaucrat::executeForm(AForm const &form) const
{
	try
	{
		form.execute(*this);
		std::cout << this->_name << " executed " << form.getName() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Error when " << this->_name << " executed "
		          << form.getName() << ". " << e.what() << std::endl;
	}
}

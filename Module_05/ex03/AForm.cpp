/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:10:24 by pablo             #+#    #+#             */
/*   Updated: 2026/04/17 15:01:37 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <ostream>

////////////////////////////////// CANONICAL ///////////////////////////////////

AForm::AForm() : _name("default"), _target("default"), _signed(false), _sign_grade(MIN_GRADE), _exec_grade(MIN_GRADE)
{
}

AForm::AForm(std::string name, const int sign_grade, const int exec_grade, std::string target)
	: _name(name), _target(target), _signed(false), _sign_grade(sign_grade), _exec_grade(exec_grade)
{
	if (sign_grade < MAX_GRADE || exec_grade < MAX_GRADE)
		throw GradeTooHighException();
	else if (sign_grade > MIN_GRADE || exec_grade > MIN_GRADE)
		throw GradeTooLowException();
}

AForm::AForm(const AForm &copy) : _name(copy._name), _target(copy._target), _signed(copy._signed), _sign_grade(copy._sign_grade), _exec_grade(copy._exec_grade)
{
}

AForm &AForm::operator=(const AForm &src)
{
	if (this != &src)
	{
		this->_target = src._target;
		this->_signed = src._signed;
	}
	return (*this);
}

AForm::~AForm()
{
}

////////////////////////////////// OPERATORS ///////////////////////////////////

std::ostream &operator<<(std::ostream &os, const AForm &f)
{
	os << f.getName() << " (target: " << f.getTarget() << "), signed: "
	<< f.getSigned()
	<< ", needs grade " << f.getSignGrade() << " for getting signed and grade "
	<< f.getExecGrade() << " for getting executed" << std::endl;
	return (os);
}

////////////////////////////////// EXCEPTIONS //////////////////////////////////

const char *AForm::GradeTooHighException::what() const throw()
{
	return ("Error: Grade too high");
}
const char *AForm::GradeTooLowException::what() const throw()
{
	return ("Error: Grade too low");
}

const char *AForm::FormNotSignedException::what() const throw()
{
	return ("Error: Form is not signed");
}

const char *AForm::InvalidTargetException::what() const throw()
{
	return ("Error: Invalid target");
}

/////////////////////////////////// GETTERS ////////////////////////////////////

std::string AForm::getName() const
{
	return (_name);
}

std::string AForm::getTarget() const
{
	return (_target);
}

bool AForm::getSigned() const
{
	return (_signed);
}

int AForm::getSignGrade() const
{
	return (_sign_grade);
}

int AForm::getExecGrade() const
{
	return (_exec_grade);
}

/////////////////////////////////// MEMBERS ////////////////////////////////////

void AForm::beSigned(const Bureaucrat &b)
{
	if (b.getGrade() > _sign_grade)
		throw GradeTooLowException();
	_signed = true;
}

void AForm::execute(Bureaucrat const &executor)
{
	if (executor.getGrade() > _exec_grade)
		throw GradeTooLowException();
	else if (!_signed)
		throw FormNotSignedException();
	else if (_target == "")
		throw InvalidTargetException();
}

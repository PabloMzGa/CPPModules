/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:10:24 by pablo             #+#    #+#             */
/*   Updated: 2026/03/18 18:57:39 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"
#include <ostream>

////////////////////////////////// CANONICAL ///////////////////////////////////

Form::Form()
{
	_name = "default";
	_signed = false;
	_sign_grade = MIN_GRADE;
	_exec_grade = MIN_GRADE;
}

Form::Form(std::string name, const int sign_grade, const int exec_grade)
{
	if (sign_grade < MAX_GRADE || exec_grade < MAX_GRADE)
		throw GradeTooHighException();
	else if (sign_grade > MIN_GRADE || exec_grade > MIN_GRADE)
		throw GradeTooLowException();
	_name = name;
	_signed = false;
	_sign_grade = sign_grade;
	_exec_grade = exec_grade;
}

Form::Form(Form &copy)
{
	*this = copy;
}

Form &Form::operator=(const Form &src)
{
	if (this != &src)
	{
		this->_name = src._name;
		this->_signed = src._signed;
		this->_sign_grade = src._sign_grade;
		this->_exec_grade = src._exec_grade;
	}
	return (*this);
}

Form::~Form() {}

////////////////////////////////// OPERATORS ///////////////////////////////////

std::ostream &operator<<(std::ostream &os, const Form &f)
{
	os << f.getName() << ", signed: " << f.getSigned() << ", needs grade "
	   << f.getSignGrade() << " for getting signed and grade "
	   << f.getExecGrade() << " for getting executed" << std::endl;
	return (os);
}

////////////////////////////////// EXCEPTIONS //////////////////////////////////

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Error: Grade too high");
}
const char *Form::GradeTooLowException::what() const throw()
{
	return ("Error: Grade too low");
}

/////////////////////////////////// GETTERS ////////////////////////////////////

std::string Form::getName() const
{
	return (_name);
}

bool Form::getSigned() const
{
	return (_signed);
}

int Form::getSignGrade() const
{
	return (_sign_grade);
}

int Form::getExecGrade() const
{
	return (_exec_grade);
}

/////////////////////////////////// MEMBERS ////////////////////////////////////

void Form::beSigned(const Bureaucrat &b)
{
	if (b.getGrade() > _sign_grade)
		throw GradeTooLowException();
	_signed = true;
}

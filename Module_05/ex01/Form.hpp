/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:01:41 by pablo             #+#    #+#             */
/*   Updated: 2026/04/17 15:00:54 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <ostream>

class Bureaucrat;

#define MAX_GRADE 1
#define MIN_GRADE 150

class Form
{
  public:
	Form();
	Form(std::string name, const int sign_grade, const int exec_grade);
	Form(const Form &copy);
	Form &operator=(const Form &src);
	~Form();

	class GradeTooHighException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};
	class GradeTooLowException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	std::string getName() const;
	bool getSigned() const;
	int getSignGrade() const;
	int getExecGrade() const;

	void beSigned(const Bureaucrat &b);

	private:
		const std::string _name;
		bool _signed;
		const int _sign_grade;
		const int _exec_grade;
};

std::ostream &operator<<(std::ostream &os, const Form &f);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:01:41 by pablo             #+#    #+#             */
/*   Updated: 2026/03/18 20:21:29 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <ostream>

class Bureaucrat;

#define MAX_GRADE 1
#define MIN_GRADE 150

class AForm
{
  public:
	AForm();
	AForm(std::string name, const int sign_grade, const int exec_grade);
	AForm(AForm &copy);
	AForm &operator=(const AForm &src);
	virtual ~AForm();

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
	class FormNotSignedException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	std::string getName() const;
	bool getSigned() const;
	int getSignGrade() const;
	int getExecGrade() const;

	void beSigned(const Bureaucrat &b);
	virtual void execute(Bureaucrat const &executor) = 0;

  private:
	std::string _name;
	bool _signed;
	int _sign_grade;
	int _exec_grade;
};

std::ostream &operator<<(std::ostream &os, const AForm &f);

#endif

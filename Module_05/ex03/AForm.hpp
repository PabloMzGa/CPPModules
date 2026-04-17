/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:01:41 by pablo             #+#    #+#             */
/*   Updated: 2026/04/17 15:01:36 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <ostream>
# include <string>

class	Bureaucrat;

# define MAX_GRADE 1
# define MIN_GRADE 150

class AForm
{
  public:
	AForm();
	AForm(std::string name, const int sign_grade, const int exec_grade,
		std::string target);
	AForm(const AForm &copy);
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
	class InvalidTargetException : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	std::string getName() const;
	std::string getTarget() const;
	bool getSigned() const;
	int getSignGrade() const;
	int getExecGrade() const;

	void beSigned(const Bureaucrat &b);
	virtual void execute(Bureaucrat const &executor) = 0;

	private:
		const std::string _name;
		std::string _target;
		bool _signed;
		const int _sign_grade;
		const int _exec_grade;
};

std::ostream &operator<<(std::ostream &os, const AForm &f);

#endif

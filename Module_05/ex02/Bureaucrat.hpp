/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:54:17 by pablo             #+#    #+#             */
/*   Updated: 2026/03/18 19:15:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <exception>
#include <string>

class AForm;

#define MAX_GRADE 1
#define MIN_GRADE 150

class Bureaucrat
{
  public:
	Bureaucrat();
	Bureaucrat(std::string name, int grade);
	Bureaucrat(Bureaucrat &copy);
	Bureaucrat &operator=(const Bureaucrat &src);
	~Bureaucrat();

	std::string getName() const;
	int getGrade() const;

	void promote(unsigned int steps);
	void demote(unsigned int steps);
	void signForm(AForm &f);

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

  private:
	std::string _name;
	int _grade;
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &b);

#endif

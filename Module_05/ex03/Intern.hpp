/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:10:01 by pablo             #+#    #+#             */
/*   Updated: 2026/03/24 20:58:06 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include <exception>

class AForm;

class Intern
{
  public:
	Intern();
	Intern(const Intern &copy);
	Intern &operator=(const Intern &src);
	~Intern();

		class FormNameNotFoundException : public std::exception
		{
			public:
				explicit FormNameNotFoundException(const std::string &name);
				virtual ~FormNameNotFoundException() throw();
				virtual const char *what() const throw();

			private:
				std::string msg;
		};

	AForm *makeForm(const std::string &formName,
	                const std::string &target) const;
};

#endif

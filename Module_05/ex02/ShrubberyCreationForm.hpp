/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:43:10 by pablo             #+#    #+#             */
/*   Updated: 2026/03/18 20:36:10 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"

#define SIGN_GRADE 145
#define EXEC_GRADE 137

class ShrubberyCreationForm : public AForm
{
  public:
	ShrubberyCreationForm(std::string name);
	virtual void execute(Bureaucrat const &executor);
};

#endif

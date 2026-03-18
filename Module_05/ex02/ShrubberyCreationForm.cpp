/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:50:10 by pablo             #+#    #+#             */
/*   Updated: 2026/03/18 20:36:36 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "AForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string name)
    : AForm(name, SIGN_GRADE, EXEC_GRADE)
{
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor)
{
	AForm::execute(executor);
}

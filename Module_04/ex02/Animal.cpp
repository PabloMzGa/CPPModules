/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:58:45 by pablo             #+#    #+#             */
/*   Updated: 2025/12/24 19:31:46 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "A_Animal.hpp"

A_Animal::A_Animal() : type("Animal")
{
	std::cout << "Animal default constructor called" << std::endl;
}

A_Animal::A_Animal(const A_Animal &copy)
{
	*this = copy;
	std::cout << "Animal copy constructor called" << std::endl;
}

A_Animal &A_Animal::operator=(const A_Animal &src)
{
	if (this != &src)
	{
		this->type = src.type;
	}
	std::cout << "Animal assignment operator called" << std::endl;
	return *this;
}

A_Animal::~A_Animal()
{
	std::cout << "Animal destructor called" << std::endl;
}

std::string A_Animal::getType() const
{
	return this->type;
}

void A_Animal::setType(const std::string &type)
{
	this->type = type;
}




/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 14:08:31 by pablo             #+#    #+#             */
/*   Updated: 2025/12/24 18:44:28 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include <iostream>

Cat::Cat() : Animal()
{
	this->type = "Cat";
	std::cout << "Cat default constructor called" << std::endl;
	this->brain = new Brain;
}

Cat::Cat(const Cat &copy) : Animal(copy)
{
	std::cout << "Cat copy constructor called" << std::endl;
	this->brain = new Brain(*copy.brain);
}

Cat &Cat::operator=(const Cat &src)
{
	std::cout << "Cat assignment operator called" << std::endl;
	if (this != &src)
	{
		Animal::operator=(src);
		delete this->brain;
		this->brain = new Brain(*src.brain);
	}
	return *this;
}

Cat::~Cat()
{
	std::cout << "Cat destructor called" << std::endl;
	delete this->brain;
}

void Cat::makeSound() const
{
	std::cout << "Meow! Meow!" << std::endl;
}

const std::string &Cat::getIdea(int index) const
{
	return this->brain->getIdea(index);
}

void Cat::setIdea(int index, const std::string &idea)
{
	this->brain->setIdea(index, idea);
}

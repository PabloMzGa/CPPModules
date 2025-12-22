/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 18:08:08 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 00:01:25 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath>
#include <iostream>

const int Fixed::n_fract_bits = 8;

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

Fixed::Fixed() : value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(int v)
{
	std::cout << "Int constructor called" << std::endl;
	value = v;
}

Fixed::Fixed(float v)
{
	std::cout << "Float constructor called" << std::endl;
	value = roundf(v * (1 << n_fract_bits));
}

Fixed::Fixed(const Fixed &copy)
{
	std::cout << "Copy constructor called" << std::endl;
	value = copy.getRawBits();
}

Fixed &Fixed::operator=(const Fixed &src)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &src)
		value = src.getRawBits();
	return (*this);
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

///////////////////////////// GETTERS & SETTERS ////////////////////////////////

int Fixed::getRawBits(void) const
{
	return value;
}

void Fixed::setRawBits(int const raw)
{
	value = raw;
}

///////////////////////////////// OPERATORS ////////////////////////////////////

std::ostream &operator<<(std::ostream &os, const Fixed &f)
{
	os << f.toFloat();
	return os;
}

///////////////////////////////// FUNCTIONS ////////////////////////////////////

float Fixed::toFloat(void) const
{
	return static_cast<float>(value) / (1 << n_fract_bits);
}

int Fixed::toInt(void) const
{
	return value / (1 << n_fract_bits);
}

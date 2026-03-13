/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 18:08:08 by pablo             #+#    #+#             */
/*   Updated: 2026/03/13 12:57:31 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath>
#include <iostream>

const int Fixed::n_fract_bits = 8;

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

Fixed::Fixed() : value(0)
{
}

Fixed::Fixed(int v)
{
	value = v * (1 << n_fract_bits);
}

Fixed::Fixed(float v)
{
	value = roundf(v * (1 << n_fract_bits));
}

Fixed::Fixed(const Fixed &copy)
{
	value = copy.getRawBits();
}

Fixed &Fixed::operator=(const Fixed &src)
{
	if (this != &src)
		value = src.getRawBits();
	return (*this);
}

Fixed::~Fixed()
{
}

/////////////////////////////// GETTERS & SETTERS
///////////////////////////////

int Fixed::getRawBits(void) const
{
	return (value);
}

void Fixed::setRawBits(int const raw)
{
	value = raw;
}

////////////////////////////////// OPERATORS //////////////////////////////////

Fixed Fixed::operator+(const Fixed &other) const
{
	Fixed result;
	result.value = this->value + other.getRawBits();
	return (result);
}

Fixed Fixed::operator-(const Fixed &other) const
{
	Fixed result;
	result.value = this->value - other.getRawBits();
	return (result);
}

Fixed Fixed::operator*(const Fixed &other) const
{
	Fixed result;
	long long num = static_cast<long long>(this->value) * static_cast<long long>(other.getRawBits());
	int div = 1 << n_fract_bits;
	long long quot = num / div;
	long long rem = num % div;
	if (rem != 0 && num < 0) {
		quot--;
	}
	result.value = static_cast<int>(quot);
	return result;
}

Fixed Fixed::operator/(const Fixed &other) const
{
	Fixed result;
	long long num = static_cast<long long>(this->value) * (1LL << n_fract_bits);
	long long den = other.getRawBits();
	long long quot = num / den;
	long long rem = num % den;
	if (rem != 0 && ((num < 0) != (den < 0))) {
		quot--;
	}
	result.value = static_cast<int>(quot);
	return result;
}

bool Fixed::operator==(const Fixed &other) const
{
	return (this->value == other.getRawBits());
}

bool Fixed::operator!=(const Fixed &other) const
{
	return (this->value != other.getRawBits());
}

bool Fixed::operator<(const Fixed &other) const
{
	return (this->value < other.getRawBits());
}

bool Fixed::operator>(const Fixed &other) const
{
	return (this->value > other.getRawBits());
}

bool Fixed::operator<=(const Fixed &other) const
{
	return (this->value <= other.getRawBits());
}

bool Fixed::operator>=(const Fixed &other) const
{
	return (this->value >= other.getRawBits());
}

Fixed &Fixed::operator++()
{
	this->value += (1 << n_fract_bits);
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed	temp;

	temp = *this;
	++(*this);
	return (temp);
}

Fixed &Fixed::operator--()
{
	this->value -= (1 << n_fract_bits);
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed	temp;

	temp = *this;
	--(*this);
	return (temp);
}

std::ostream &operator<<(std::ostream &os, const Fixed &f)
{
	os << f.toFloat();
	return (os);
}

///////////////////////////////// FUNCTIONS ////////////////////////////////////

float Fixed::toFloat(void) const
{
	return (static_cast<float>(value) / (1 << n_fract_bits));
}

int Fixed::toInt(void) const
{
	return (value / (1 << n_fract_bits));
}

const Fixed &Fixed::min(const Fixed &f1, const Fixed &f2)
{
	if (f1 < f2)
		return (f1);
	else
		return (f2);
}

Fixed &Fixed::min(Fixed &f1, Fixed &f2)
{
	if (f1 < f2)
		return (f1);
	else
		return (f2);
}

const Fixed &Fixed::max(const Fixed &f1, const Fixed &f2)
{
	if (f1 > f2)
		return (f1);
	else
		return (f2);
}

Fixed &Fixed::max(Fixed &f1, Fixed &f2)
{
	if (f1 > f2)
		return (f1);
	else
		return (f2);
}

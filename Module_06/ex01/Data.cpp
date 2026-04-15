/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:05:00 by pablo             #+#    #+#             */
/*   Updated: 2026/04/15 18:58:33 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data::Data() : _value(0)
{
}

Data::Data(const Data &src)
{
	*this = src;
}

Data &Data::operator=(const Data &rhs)
{
	if (this != &rhs)
		_value = rhs._value;
	return (*this);
}

Data::~Data()
{
}

int	Data::getValue() const
{
	return (_value);
}

void	Data::setValue(int value)
{
	_value = value;
}

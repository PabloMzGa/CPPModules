/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:32:29 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 16:59:54 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

Point::Point() : x(0), y(0) {}

Point::Point(const Point &point) : x(point.x), y(point.y) {}

Point::Point(const float x_value, const float y_value) : x(x_value), y(y_value)
{
}

Point &Point::operator=(const Point &src)
{
	if (this != &src)
	{
		x = src.x;
		y = src.y;
	}
	return *this;
}

Point::~Point() {}

///////////////////////////// GETTERS & SETTERS ////////////////////////////////

Fixed Point::get_x() const
{
	return x;
}
Fixed Point::get_y() const
{
	return y;
}

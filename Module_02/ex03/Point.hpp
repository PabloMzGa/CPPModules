/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:28:51 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 16:59:58 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP
#include "Fixed.hpp"

class Point
{
  private:
	Fixed x;
	Fixed y;

  public:
	Point();
	Point(const Point &point);
	Point(const float x_value, const float y_value);
	Point &operator=(const Point &src);
	~Point();

	Fixed get_x() const;
	Fixed get_y() const;
};

#endif

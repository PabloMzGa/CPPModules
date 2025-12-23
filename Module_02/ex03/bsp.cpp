/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:46:26 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 17:29:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include <iostream>

/**
 * @brief Calculates the area of a triangle formed by three points using the
 * shoelace formula.
 *
 * This static function computes the area of the triangle defined by points a,
 * b, and c. The shoelace formula is applied to determine the area, which is
 * then multiplied by 0.5 to account for the formula's derivation.
 *
 * @param a The first vertex of the triangle.
 * @param b The second vertex of the triangle.
 * @param c The third vertex of the triangle.
 * @return The computed area of the triangle as a Fixed type.
 */
static Fixed calculate_tri_area(Point const a, Point const b, Point const c)
{
	Fixed triangle_area;

	triangle_area = (a.get_x() * (b.get_y() - c.get_y()) +
					 b.get_x() * (c.get_y() - a.get_y()) +
					 c.get_x() * (a.get_y() - b.get_y())) *
					Fixed(0.5f);
	return (triangle_area);
}

/**
 * @brief Determines if a point is inside a triangle using the barycentric
 * coordinate system (area method).
 *
 * This function checks if the given point is inside the triangle formed by
 * points a, b, and c. It calculates the area of the main triangle and the
 * areas of the three subtriangles formed by the point and the triangle's
 * vertices. If the sum of the subtriangle areas equals the main triangle
 * area and all subtriangle areas are non-negative, the point is inside.
 *
 * @param a The first vertex of the triangle.
 * @param b The second vertex of the triangle.
 * @param c The third vertex of the triangle.
 * @param point The point to check for inclusion in the triangle.
 * @return true if the point is inside the triangle (including on the
 * boundary), false otherwise. Also returns false if the triangle is
 * degenerate (area zero).
 */
bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed triangle_area;
	Fixed sub1, sub2, sub3;

	triangle_area = calculate_tri_area(a, b, c);
	if (triangle_area == 0)
	{
		std::cout << "ERROR: Triangle malformed!" << std::endl;
		return (false);
	}
	sub1 = calculate_tri_area(point, b, c);
	sub2 = calculate_tri_area(a, point, c);
	sub3 = calculate_tri_area(a, b, point);

	if (triangle_area == sub1 + sub2 + sub3 &&
		sub1 >= 0 && sub2 >= 0 && sub3 >= 0)
		return (true);
	else
		return (false);
}

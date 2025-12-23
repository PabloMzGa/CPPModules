/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 23:54:47 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 17:39:38 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include <iostream>

bool bsp(Point const a, Point const b, Point const c, Point const point);

int main(void)
{
	// Test case 1: Point inside the triangle
	Point a(0, 0), b(4, 0), c(0, 3);
	Point p_inside(1, 1);
	std::cout << "Point inside (1,1) in triangle (0,0)-(4,0)-(0,3): "
	          << (bsp(a, b, c, p_inside) ? "true" : "false") << std::endl;

	// Test case 2: Point outside the triangle
	Point p_outside(5, 5);
	std::cout << "Point outside (5,5): "
	          << (bsp(a, b, c, p_outside) ? "true" : "false") << std::endl;

	// Test case 3: Point on edge
	Point p_on_edge(2, 0);
	std::cout << "Point on edge (2,0): "
	          << (bsp(a, b, c, p_on_edge) ? "true" : "false") << std::endl;

	// Test case 4: Point on vertex
	Point p_on_vertex(0, 0);
	std::cout << "Point on vertex (0,0): "
	          << (bsp(a, b, c, p_on_vertex) ? "true" : "false") << std::endl;

	// Test case 5: Degenerate triangle (collinear points)
	Point d(0, 0), e(2, 0), f(4, 0);
	Point p_degen(1, 0);
	std::cout << "Degenerate triangle (0,0)-(2,0)-(4,0), point (1,0): "
	          << (bsp(d, e, f, p_degen) ? "true" : "false") << std::endl;

	// Test case 6: Triangle in clockwise order (negative orientation)
	Point g(0, 0), h(0, 3), i(4, 0); // Clockwise order
	Point p_cw(1, 1);
	std::cout << "Clockwise triangle (0,0)-(0,3)-(4,0), point (1,1): "
	          << (bsp(g, h, i, p_cw) ? "true" : "false") << std::endl;

	return 0;
}

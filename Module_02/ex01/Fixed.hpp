/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:52:34 by pablo             #+#    #+#             */
/*   Updated: 2026/01/12 17:27:09 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
  private:
	int value;
	static const int n_fract_bits;

  public:
	Fixed();
	Fixed(int v);
	Fixed(float v);
	Fixed(const Fixed &copy);
	Fixed &operator=(const Fixed &src);
	~Fixed();

	int getRawBits(void) const;
	void setRawBits(int const raw);

	float toFloat(void) const;
	int toInt(void) const;

};

std::ostream &operator<<(std::ostream &os, const Fixed &f);

#endif

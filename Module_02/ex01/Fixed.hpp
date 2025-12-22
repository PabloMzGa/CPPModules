/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:52:34 by pablo             #+#    #+#             */
/*   Updated: 2025/12/22 23:47:08 by pablo            ###   ########.fr       */
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

	friend std::ostream &operator<<(std::ostream &os, const Fixed &f);
};

#endif

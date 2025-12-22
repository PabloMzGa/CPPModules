/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:52:34 by pablo             #+#    #+#             */
/*   Updated: 2025/12/19 18:09:15 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed
{
  private:
	int value;
	static const int n_fract_bits;
  public:
	Fixed();
	Fixed(const Fixed &copy);
	Fixed &operator=(const Fixed &src);
	~Fixed();

	int getRawBits(void) const;
	void setRawBits( int const raw );
};

#endif

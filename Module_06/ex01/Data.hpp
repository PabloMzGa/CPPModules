/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:05:00 by pablo             #+#    #+#             */
/*   Updated: 2026/04/15 18:58:31 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP

class Data
{
	private:
		int	_value;

	public:
		Data();
		Data(const Data &src);
		Data &operator=(const Data &rhs);
		~Data();

		int	getValue() const;
		void	setValue(int value);
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:59:43 by pablo             #+#    #+#             */
/*   Updated: 2026/03/13 14:33:57 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap
{
  public:
	static const unsigned int BASE_HP  = 100;
	static const unsigned int BASE_EP  = 100;
	static const unsigned int BASE_ATK = 30;

	FragTrap();
	FragTrap(std::string name);
	FragTrap(const FragTrap &copy);
	FragTrap &operator=(const FragTrap &src);
	~FragTrap();

	void highFivesGuys(void);
};

#endif

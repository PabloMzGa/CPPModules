/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:25:16 by pablo             #+#    #+#             */
/*   Updated: 2025/12/23 19:56:01 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>

class ClapTrap
{
  private:
	std::string name;
	unsigned int hp;
	unsigned int ep;
	unsigned int atk_dmg;

  public:
	ClapTrap();
	ClapTrap(std::string name);
	ClapTrap(const ClapTrap &copy);
	ClapTrap &operator=(const ClapTrap &src);
	~ClapTrap();

	void attack(const std::string &target);
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);
};

#endif

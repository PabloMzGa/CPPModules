/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:11:40 by pablo             #+#    #+#             */
/*   Updated: 2025/12/13 14:30:48 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <string>

class HumanB
{
  public:
	HumanB(std::string name);
	void attack();
	void setWeapon(Weapon &weapon);

  private:
	std::string _name;
	Weapon *_weapon;
};

#endif

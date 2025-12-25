/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:16:21 by pablo             #+#    #+#             */
/*   Updated: 2025/12/25 16:53:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"

class Character : public ICharacter
{
  public:
	Character(std::string name);
	Character(const Character &copy);
	Character &operator=(const Character &src);
	virtual ~Character();

	virtual std::string const &getName() const ;
	virtual void equip(AMateria *m);
	virtual void unequip(int idx);
	virtual void use(int idx, ICharacter &target);

  private:
	std::string name;
	AMateria *inventory[4];
	AMateria **floor;
	int floorSize;
	int floorCapacity;



};

#endif

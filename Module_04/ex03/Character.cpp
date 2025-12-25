/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:22:40 by pablo             #+#    #+#             */
/*   Updated: 2025/12/25 17:01:34 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include <iostream>

/////////////////////////////// ORTHODOX METHODS ///////////////////////////////

Character::Character(std::string name)
{
	this->name = name;
	for (int i = 0; i < 4; i++)
		inventory[i] = NULL;
	floorCapacity = 10;
	floor = new AMateria*[floorCapacity];
	for (int i = 0; i < floorCapacity; i++)
		floor[i] = NULL;
	floorSize = 0;
}

Character::Character(const Character &copy)
{
	this->name = copy.name;
	floorCapacity = copy.floorCapacity;
	floor = new AMateria*[floorCapacity];
	floorSize = copy.floorSize;
	for (int i = 0; i < floorCapacity; i++)
	{
		if (i < copy.floorSize && copy.floor[i])
			floor[i] = copy.floor[i]->clone();
		else
			floor[i] = NULL;
	}
	for (int i = 0; i < 4; i++)
	{
		if (copy.inventory[i])
			inventory[i] = copy.inventory[i]->clone();
		else
			inventory[i] = NULL;
	}
}

Character &Character::operator=(const Character &src)
{
	if (this != &src)
	{
		this->name = src.name;
		for (int i = 0; i < 4; i++)
		{
			delete inventory[i];
			inventory[i] = NULL;
		}
		for (int i = 0; i < floorSize; i++)
		{
			delete floor[i];
		}
		delete[] floor;
		floorCapacity = src.floorCapacity;
		floor = new AMateria*[floorCapacity];
		floorSize = src.floorSize;
		for (int i = 0; i < floorCapacity; i++)
		{
			if (i < src.floorSize && src.floor[i])
				floor[i] = src.floor[i]->clone();
			else
				floor[i] = NULL;
		}
		for (int i = 0; i < 4; i++)
		{
			if (src.inventory[i])
				inventory[i] = src.inventory[i]->clone();
			else
				inventory[i] = NULL;
		}
	}
	return (*this);
}

Character::~Character()
{
	for (int i = 0; i < 4; i++)
	{
		delete inventory[i];
	}
	for (int i = 0; i < floorSize; i++)
	{
		delete floor[i];
	}
	delete[] floor;
}

/////////////////////////////// GETTERS & SETTERS //////////////////////////////

std::string const &Character::getName() const
{
	return name;
}

/////////////////////////////////// FUNCTIONS //////////////////////////////////

void Character::equip(AMateria *m)
{
	for (size_t i = 0; i < 4; i++)
	{
		if (inventory[i] == NULL)
		{
			inventory[i] = m;
			std::cout << "Materia " << m->getType() << " equiped!" << std::endl;
			return;
		}

	}
	std::cout << "Inventory full!" << std::endl;
}

void Character::unequip(int idx) {
    if (idx >= 0 && idx < 4 && inventory[idx]) {
        if (floorSize == floorCapacity) {
            int newCapacity = floorCapacity * 2;
            AMateria **newFloor = new AMateria*[newCapacity];
            for (int i = 0; i < newCapacity; i++) {
                if (i < floorSize)
                    newFloor[i] = floor[i];
                else
                    newFloor[i] = NULL;
            }
            delete[] floor;
            floor = newFloor;
            floorCapacity = newCapacity;
        }
        floor[floorSize] = inventory[idx];
        floorSize++;
        inventory[idx] = NULL;
    }
}

void Character::use(int idx, ICharacter &target)
{
	if (!inventory[idx])
	{
		std::cout << "Empty slot!" << std::endl;
		return;
	}
	inventory[idx]->use(target);
}

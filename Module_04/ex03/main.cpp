/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:50:49 by pablo             #+#    #+#             */
/*   Updated: 2025/12/25 17:12:36 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"
#include <iostream>

int main()
{
	IMateriaSource *src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(new Ice()); // Inventory full, MateriaSource will delete it

	Character *me = new Character("me");
	AMateria *tmp;

	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	// Inventory full, this should warn and NOT equip
	tmp = src->createMateria("ice");
	me->equip(tmp);
	delete tmp;

	Character *bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	me->use(2, *bob);
	me->use(3, *bob);

	// Unequip a slot and check it goes to floor
	me->unequip(1);
	me->use(1, *bob); // now empty

	// Copy via constructor (deep copy of inventory)
	Character copy(*me);
	copy.use(0, *bob);

	// Assignment (deep copy)
	Character other("other");
	other = copy;
	other.use(0, *bob);

	// Unknown materia
	AMateria *bad = src->createMateria("fire");
	if (!bad)
		std::cout << "Unknown materia returns NULL" << std::endl;

	delete bob;
	delete me;
	delete src;
	return 0;
}

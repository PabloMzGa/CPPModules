/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 14:21:26 by pablo             #+#    #+#             */
/*   Updated: 2025/12/24 18:22:51 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main()
{
	std::cout << "=== Polymorphism Test with Animal, Dog and Cat ===" << std::endl;
	const Animal *meta = new Animal();
	const Animal *j = new Dog();
	const Animal *i = new Cat();
	std::cout << j->getType() << std::endl;
	std::cout << i->getType() << std::endl;
	i->makeSound(); // Should output "Meow! Meow!" (polymorphism)
	j->makeSound(); // Should output "Woof! Woof!"
	meta->makeSound(); // Should output "Some generic animal sound"
	delete meta;
	delete j;
	delete i;

	std::cout << "\n=== No Polymorphism Test with WrongAnimal and WrongCat ===" << std::endl;
	const WrongAnimal *wrongMeta = new WrongAnimal();
	const WrongAnimal *wrongI = new WrongCat();
	std::cout << wrongI->getType() << std::endl;
	wrongI->makeSound(); // Should output "Wrong animal sound" (no polymorphism)
	wrongMeta->makeSound(); // Should output "Wrong animal sound"
	delete wrongMeta;
	delete wrongI; // Since WrongAnimal destructor isn't virtual,
			       // it'll call only WrongAnimal destructor, not WrongCat's

	std::cout << "\n=== Getters and Setters Test ===" << std::endl;
	Animal *animal = new Dog();
	std::cout << "Initial type: " << animal->getType() << std::endl;
	animal->setType("SuperDog");
	std::cout << "Type after setType: " << animal->getType() << std::endl;
	animal->makeSound();
	delete animal;

	std::cout << "\nEnd of testing." << std::endl;
	return 0;
}

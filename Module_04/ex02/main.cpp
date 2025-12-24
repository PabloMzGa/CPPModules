/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 14:21:26 by pablo             #+#    #+#             */
/*   Updated: 2025/12/24 19:32:43 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A_Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

#include <iostream>

int main()
{
std::cout << "=========================================" << std::endl;
std::cout << "=== Section: Basic Creation Test ===" << std::endl;
std::cout << "=========================================" << std::endl;
const A_Animal* j = new Dog();
const A_Animal* i = new Cat();
delete j;
delete i;

std::cout << "\n=========================================" << std::endl;
std::cout << "=== Section: Deep Copy Test for Dog ===" << std::endl;
std::cout << "=========================================" << std::endl;
Dog dog1;
dog1.setIdea(0, "Original dog idea");
Dog dog2 = dog1;  // copy constructor
dog2.setIdea(0, "Modified dog idea");
std::cout << "dog1 idea: " << dog1.getIdea(0) << std::endl;
std::cout << "dog2 idea: " << dog2.getIdea(0) << std::endl;

std::cout << "\n=========================================" << std::endl;
std::cout << "=== Section: Deep Copy Test for Cat ===" << std::endl;
std::cout << "=========================================" << std::endl;
Cat cat1;
cat1.setIdea(0, "Original cat idea");
Cat cat2;
cat2 = cat1;  // assignment operator
cat2.setIdea(0, "Modified cat idea");
std::cout << "cat1 idea: " << cat1.getIdea(0) << std::endl;
std::cout << "cat2 idea: " << cat2.getIdea(0) << std::endl;

std::cout << "\n=========================================" << std::endl;
std::cout << "=== Section: Animal Array Test ===" << std::endl;
std::cout << "=========================================" << std::endl;
const A_Animal* animals[100];
for (size_t i = 0; i < 50; i++)
{
	animals[i] = new Dog();
}
for (size_t i = 50; i < 100; i++)
{
	animals[i] = new Cat();
}
for (size_t i = 0; i < 100; i++)
{
	delete animals[i];
}

std::cout << "\n=========================================" << std::endl;
std::cout << "=== Section: Abstract Class Instantiation Test ===" << std::endl;
std::cout << "=========================================" << std::endl;
// Attempting to instantiate A_Animal directly should fail
// Uncomment the next line to see the compilation error:
// A_Animal animal;  // Error: cannot declare variable 'animal' to be of abstract type 'A_Animal'
std::cout << "A_Animal is abstract and cannot be instantiated directly." << std::endl;

return 0;
}

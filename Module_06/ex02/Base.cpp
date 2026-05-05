/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:44:33 by pablo             #+#    #+#             */
/*   Updated: 2026/05/05 20:49:29 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base::~Base() {}

Base *Base::generate()
{
	static bool seeded = false;
	if (!seeded)
	{
		std::srand(static_cast<unsigned int>(std::time(NULL)));
		seeded = true;
	}

	int r = std::rand() % 3;
	if (r == 0)
	{
		std::cout << "Generated A" << std::endl;
		return new A();
	}
	else if (r == 1)
	{
		std::cout << "Generated B" << std::endl;
		return new B();
	}
	std::cout << "Generated C" << std::endl;
	return new C();
}

void Base::identify(Base *p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "Pointer is A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "Pointer is B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "Pointer is C" << std::endl;
	else
		std::cout << "Error identifying pointer" << std::endl;
}

void Base::identify(Base &p)
{
	try
	{
		(void)dynamic_cast<A &>(p);
		std::cout << "Pointer is A" << std::endl;
		return;
	}
	catch (const std::exception &)
	{
	}
	try
	{
		(void)dynamic_cast<B &>(p);
		std::cout << "Pointer is B" << std::endl;
		return;
	}
	catch (const std::exception &)
	{
	}
	try
	{
		(void)dynamic_cast<C &>(p);
		std::cout << "Pointer is C" << std::endl;
		return;
	}
	catch (const std::exception &)
	{
	}
	std::cout << "Error identifying pointer" << std::endl;
}

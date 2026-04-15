/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 20:30:00 by pablo             #+#    #+#             */
/*   Updated: 2026/04/15 20:12:04 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <iostream>

int main(void)
{
	Base tester;

	for (int i = 0; i < 10; ++i)
	{
		std::cout << "---- Test " << (i + 1) << " ----" << std::endl;
		Base *ptr = Base::generate();
		tester.identify(ptr);
		tester.identify(*ptr);
		delete ptr;
	}
	return (0);
}
